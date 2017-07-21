#include "Game.h"
#include "PhysicsComponent.h"
#include "Velocity.h"
#include "VelocityComponent.h"
#include "KeyboardDirectionInputComponent.h"
#include "AnimationGraphicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "ColorGraphicsComponent.h"
#include "AStarComponent.h"
#include "PathGoalComponent.h"
#include "PointsCollectorComponent.h"
#include "WinConditionComponent.h"
#include "ScoreGraphicsComponent.h"
#include "ScoreWatcherComponent.h"
#include "IdleAnimationComponent.h"
#include "TeleportComponent.h"
#include "BreadcrumbTrailComponent.h"
#include "BreadcrumbFollowerComponent.h"
#include "PseudoRandomDirectionComponent.h"

// TODO: Move metadata to XML so this method is less bloated?
bool Game::createEntities() {
	// Draw order: walls == pellets == powerups < cap-man < ghosts

	std::vector<int> layout = mMap.layout();

	// Prepare the teleport pads; both Cap-Man and the Ghosts use the same ones
	int portalRow = 10;
	Point portA(-1, portalRow);
	Point portB(mMap.columns(), portalRow);
	mMap.scaleUnitsToPixels(portA);
	mMap.scaleUnitsToPixels(portB);
	Rect portPadA(portA.x(), portA.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());
	Rect portPadB(portB.x(), portB.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());
	TeleportComponent teleportComponent(portPadA, Directions::RIGHT, portPadB, Directions::LEFT);

	// Background/walls
	{
		int background = mManager.createEntity();
		std::unordered_map<int, Animation> backgroundAnimations;
		Animation backgroundAnimation;
		backgroundAnimation.addSprite(std::move(mSpriteRepository.findSprite("background_walls")));
		backgroundAnimations.insert_or_assign(AnimationStates::DEFAULT, std::move(backgroundAnimation));

		mManager.addComponent(background, PhysicsComponent(0, 0, mWindow.width(), mWindow.height()));
		mManager.addComponent(background, AnimationGraphicsComponent(std::move(backgroundAnimations), AnimationStates::DEFAULT));
		mManager.registerEntity(background);
	}

	// Pellets
	{
		// TODO: Magic numbers
		int pelletSideLength = mMap.singleUnitPixels() / 4;
		int pelletPadding = (mMap.singleUnitPixels() - pelletSideLength) / 2;
		for (size_t i = 0; i < layout.size(); ++i) {
			if (layout.at(i) == MapLayoutElements::PELLET) {
				int pellet = mManager.createEntity();
				Point pelletLocation = mMap.mapLocation(i, true);
				Rect rect(pelletLocation.x() + pelletPadding,
					pelletLocation.y() + pelletPadding,
					pelletSideLength,
					pelletSideLength);
				mManager.addComponent(pellet, PhysicsComponent(rect));
				mManager.addComponent(pellet, ColorGraphicsComponent(Colors::BEIGE));
				mManager.registerEntity(pellet);

				mPellets.insert_or_assign(i, pellet);
			}
		}
	}

	// Powerups
	{
		Sprite powerupAsset = std::move(mSpriteRepository.findSprite("powerup"));
		int powerupSideLength = powerupAsset.width() * mMap.scaleMultiplier();
		Rect powerupDimens(-1, -1, powerupSideLength, powerupSideLength);
		int powerupPadding = powerupSideLength / 2;
		for (size_t i = 0; i < layout.size(); ++i) {
			if (layout.at(i) == MapLayoutElements::POWERUP) {
				int powerup = mManager.createEntity();
				Point powerupLocation = mMap.mapLocation(i, true);
				powerupDimens.setLeft(powerupLocation.x() + powerupPadding);
				powerupDimens.setTop(powerupLocation.y() + powerupPadding);
				mManager.addComponent(powerup, PhysicsComponent(powerupDimens));

				std::unordered_map<int, Animation> powerupAnimations;
				Animation powerupAnimation(GameConstants::POWERUP_BLINKING_INTERVAL);
				powerupAnimation.addSprite(std::move(powerupAsset));
				powerupAnimation.addSprite(std::move(mSpriteRepository.findSprite("powerup_off")));
				powerupAnimations.insert_or_assign(AnimationStates::DEFAULT, std::move(powerupAnimation));
				mManager.addComponent(powerup, AnimationGraphicsComponent(std::move(powerupAnimations), AnimationStates::DEFAULT));
				mManager.addComponent(powerup, IdleAnimationComponent());
				mManager.registerEntity(powerup);

				mPowerups.insert_or_assign(i, powerup);
			}
		}
	}

	// Cap-Man
	{
		mCapMan = mManager.createEntity();

		std::unordered_map<int, Animation> capManAnimations;
		Animation walkLeft(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkLeft.addSprite(std::move(mSpriteRepository.findSprite("capman_closed")));
		walkLeft.addSprite(std::move(mSpriteRepository.findSprite("capman_left1")));
		walkLeft.addSprite(std::move(mSpriteRepository.findSprite("capman_left2")));
		walkLeft.addSprite(std::move(mSpriteRepository.findSprite("capman_left1")));
		capManAnimations.insert_or_assign(AnimationStates::WALK_LEFT, walkLeft);
		Animation walkRight(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkRight.addSprite(std::move(mSpriteRepository.findSprite("capman_closed")));
		walkRight.addSprite(std::move(mSpriteRepository.findSprite("capman_right1")));
		walkRight.addSprite(std::move(mSpriteRepository.findSprite("capman_right2")));
		walkRight.addSprite(std::move(mSpriteRepository.findSprite("capman_right1")));
		capManAnimations.insert_or_assign(AnimationStates::WALK_RIGHT, walkRight);
		Animation walkUp(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkUp.addSprite(std::move(mSpriteRepository.findSprite("capman_closed")));
		walkUp.addSprite(std::move(mSpriteRepository.findSprite("capman_up1")));
		walkUp.addSprite(std::move(mSpriteRepository.findSprite("capman_up2")));
		walkUp.addSprite(std::move(mSpriteRepository.findSprite("capman_up1")));
		capManAnimations.insert_or_assign(AnimationStates::WALK_UP, walkUp);
		Animation walkDown(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkDown.addSprite(std::move(mSpriteRepository.findSprite("capman_closed")));
		walkDown.addSprite(std::move(mSpriteRepository.findSprite("capman_down1")));
		walkDown.addSprite(std::move(mSpriteRepository.findSprite("capman_down2")));
		walkDown.addSprite(std::move(mSpriteRepository.findSprite("capman_down1")));
		capManAnimations.insert_or_assign(AnimationStates::WALK_DOWN, walkDown);
		Animation stationaryLeft;
		stationaryLeft.addSprite(std::move(mSpriteRepository.findSprite("capman_left1")));
		capManAnimations.insert_or_assign(AnimationStates::STATIONARY_LEFT, stationaryLeft);
		Animation stationaryRight;
		stationaryRight.addSprite(std::move(mSpriteRepository.findSprite("capman_right1")));
		capManAnimations.insert_or_assign(AnimationStates::STATIONARY_RIGHT, stationaryRight);
		Animation stationaryUp;
		stationaryUp.addSprite(std::move(mSpriteRepository.findSprite("capman_up1")));
		capManAnimations.insert_or_assign(AnimationStates::STATIONARY_UP, stationaryUp);
		Animation stationaryDown;
		stationaryDown.addSprite(std::move(mSpriteRepository.findSprite("capman_down1")));
		capManAnimations.insert_or_assign(AnimationStates::STATIONARY_DOWN, stationaryDown);
		Animation death(GameConstants::ANIMATION_FRAME_INTERVAL);
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death1")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death2")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death3")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death4")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death5")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death6")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death7")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death8")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death9")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death10")));
		death.addSprite(std::move(mSpriteRepository.findSprite("capman_death11")));
		capManAnimations.insert_or_assign(AnimationStates::DEATH, death);
		Velocity velocity(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED), 0);
		float speed = static_cast<float>(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED));

		int capManStart = mMap.indexOf(MapLayoutElements::CAP_MAN);
		Point startPoint = mMap.mapLocation(capManStart, true /* scaleUnitsToPixels */);

		// Start Cap-Man off as if a left key were pressed
		mKeyboard.setRecentKeyDown(Keys::LEFT);

		mManager.addComponent(mCapMan, KeyboardDirectionInputComponent(mKeyboard, Directions::LEFT));
		mManager.addComponent(mCapMan, VelocityComponent(velocity, speed));
		mManager.addComponent(mCapMan, PhysicsComponent(startPoint.x(), startPoint.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels()));
		mManager.addComponent(mCapMan, AnimationGraphicsComponent(std::move(capManAnimations), AnimationStates::WALK_LEFT));
		mManager.addComponent(mCapMan, LastValidDirectionComponent(Directions::LEFT));
		mManager.addComponent(mCapMan, PointsCollectorComponent());
		mManager.addComponent(mCapMan, WinConditionComponent());
		mManager.addComponent(mCapMan, std::move(teleportComponent));
		mManager.addComponent(mCapMan, BreadcrumbTrailComponent());
		mManager.registerEntity(mCapMan);
	}

	// Ghosts
	{
		std::vector<std::string> ghostNames = { "inky", "blinky", "pinky", "clyde" };
		for (const auto& ghostName : ghostNames) {

			int ghost = mManager.createEntity();

			std::unordered_map<int, Animation> ghostAnimations;
			Animation walkLeft(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkLeft.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_left1")));
			walkLeft.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_left2")));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_LEFT, walkLeft);
			Animation walkRight(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkRight.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_right1")));
			walkRight.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_right2")));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_RIGHT, walkRight);
			Animation walkUp(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkUp.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_up1")));
			walkUp.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_up2")));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_UP, walkUp);
			Animation walkDown(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkDown.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_down1")));
			walkDown.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_down2")));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_DOWN, walkDown);

			Animation startionaryLeft;
			startionaryLeft.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_left2")));
			ghostAnimations.insert_or_assign(AnimationStates::STATIONARY_LEFT, startionaryLeft);
			Animation stationaryRight;
			stationaryRight.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_right1")));
			ghostAnimations.insert_or_assign(AnimationStates::STATIONARY_RIGHT, stationaryRight);
			Animation stationaryUp;
			stationaryUp.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_up2")));
			ghostAnimations.insert_or_assign(AnimationStates::STATIONARY_UP, stationaryUp);
			Animation stationaryDown;
			stationaryDown.addSprite(std::move(mSpriteRepository.findSprite(ghostName + "_down1")));
			ghostAnimations.insert_or_assign(AnimationStates::STATIONARY_DOWN, stationaryDown);

			Animation deathLeft;
			deathLeft.addSprite(std::move(mSpriteRepository.findSprite("ghost_death_left")));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_LEFT, deathLeft);
			Animation deathRight;
			deathRight.addSprite(std::move(mSpriteRepository.findSprite("ghost_death_right")));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_RIGHT, deathRight);
			Animation deathUp;
			deathUp.addSprite(std::move(mSpriteRepository.findSprite("ghost_death_up")));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_UP, deathUp);
			Animation deathDown;
			deathDown.addSprite(std::move(mSpriteRepository.findSprite("ghost_death_down")));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_DOWN, deathDown);

			Animation vulnerable(GameConstants::ANIMATION_FRAME_INTERVAL);
			vulnerable.addSprite(std::move(mSpriteRepository.findSprite("ghost_blue1")));
			vulnerable.addSprite(std::move(mSpriteRepository.findSprite("ghost_blue2")));
			ghostAnimations.insert_or_assign(AnimationStates::VULNERABLE, deathDown);
			// TODO: move to constant
			// TODO: vulnerable expiring faster?
			Animation vulnerableExpiring(264 /* millis */);
			vulnerableExpiring.addSprite(std::move(mSpriteRepository.findSprite("ghost_blue1")));
			vulnerableExpiring.addSprite(std::move(mSpriteRepository.findSprite("ghost_white1")));
			vulnerableExpiring.addSprite(std::move(mSpriteRepository.findSprite("ghost_blue2")));
			vulnerableExpiring.addSprite(std::move(mSpriteRepository.findSprite("ghost_white2")));
			ghostAnimations.insert_or_assign(AnimationStates::VULNERABLE_EXPIRING, vulnerableExpiring);

			// TODO: set initial velocity
			Velocity velocity;
			float speed = static_cast<float>(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED));

			int ghostStart;
			PathGoalComponent pathGoalComponent;

			// TODO: Refactor
			if (ghostName == ghostNames.at(0)) {
				ghostStart = mMap.indexOf(MapLayoutElements::INKY);
				pathGoalComponent.setGoal(Point(11, 10));
			} else if (ghostName == ghostNames.at(1)) {
				ghostStart = mMap.indexOf(MapLayoutElements::BLINKY);
				pathGoalComponent.setGoal(Point(2, 2));
			} else if (ghostName == ghostNames.at(2)) {
				ghostStart = mMap.indexOf(MapLayoutElements::PINKY);
				pathGoalComponent.setGoal(Point(9, 10));
			} else {
				ghostStart = mMap.indexOf(MapLayoutElements::CLYDE);
				pathGoalComponent.setGoal(Point(18, 2));
			}

			Point startPoint = mMap.mapLocation(ghostStart, true /* scaleUnitsToPixels */);

			mManager.addComponent(ghost, AStarComponent(mMap));
			mManager.addComponent(ghost, std::move(pathGoalComponent));
			mManager.addComponent(ghost, DirectionInputComponent());
			mManager.addComponent(ghost, VelocityComponent(velocity, speed));
			mManager.addComponent(ghost, PhysicsComponent(startPoint.x(), startPoint.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels()));
			mManager.addComponent(ghost, AnimationGraphicsComponent(std::move(ghostAnimations), AnimationStates::STATIONARY_DOWN));
			mManager.addComponent(ghost, LastValidDirectionComponent(Directions::DOWN));
			mManager.addComponent(ghost, std::move(teleportComponent));
			mManager.addComponent(ghost, BreadcrumbFollowerComponent(mCapMan));
			mManager.addComponent(ghost, PseudoRandomDirectionComponent(GameConstants::GHOST_DIRECTION_CHANGE_INTERVAL));
			mManager.registerEntity(ghost);
		}
	}

	// Score
	{
		int score = mManager.createEntity();
		std::unordered_map<int, Sprite> numberSprites;
		numberSprites.insert_or_assign(0, std::move(mSpriteRepository.findSprite("text_0")));
		numberSprites.insert_or_assign(1, std::move(mSpriteRepository.findSprite("text_1")));
		numberSprites.insert_or_assign(2, std::move(mSpriteRepository.findSprite("text_2")));
		numberSprites.insert_or_assign(3, std::move(mSpriteRepository.findSprite("text_3")));
		numberSprites.insert_or_assign(4, std::move(mSpriteRepository.findSprite("text_4")));
		numberSprites.insert_or_assign(5, std::move(mSpriteRepository.findSprite("text_5")));
		numberSprites.insert_or_assign(6, std::move(mSpriteRepository.findSprite("text_6")));
		numberSprites.insert_or_assign(7, std::move(mSpriteRepository.findSprite("text_7")));
		numberSprites.insert_or_assign(8, std::move(mSpriteRepository.findSprite("text_8")));
		numberSprites.insert_or_assign(9, std::move(mSpriteRepository.findSprite("text_9")));

		mManager.addComponent(score, ScoreGraphicsComponent(std::move(numberSprites)));
		int marginTop = mMap.singleUnitPixels() / 4;
		int marginLeft = mMap.singleUnitPixels();
		int w = mMap.singleUnitPixels() / 2;
		int h = mMap.singleUnitPixels() / 2;
		// This PhysicsComponent is the AABB location of the first digit of the score
		mManager.addComponent(score, PhysicsComponent(marginLeft, marginTop, w, h));
		mManager.addComponent(score, ScoreWatcherComponent(mCapMan));
		mManager.registerEntity(score);
	}

	// 1-up
	{
		int oneUpEntity = mManager.createEntity();

		Sprite oneUpSprite = std::move(mSpriteRepository.findSprite("text_1up"));
		int marginLeft = (mMap.columns() - 1) * mMap.singleUnitPixels() - oneUpSprite.width() * mMap.scaleMultiplier();
		int marginTop = mMap.singleUnitPixels() / 4;
		int w = oneUpSprite.width() * mMap.scaleMultiplier();
		int h = oneUpSprite.height() * mMap.scaleMultiplier();

		std::unordered_map<int, Animation> oneUpAnimations;
		Animation oneUpAnimation(GameConstants::ONE_UP_BLINKING_INTERVAL);
		oneUpAnimation.addSprite(std::move(oneUpSprite));
		oneUpAnimation.addSprite(std::move(mSpriteRepository.findSprite("text_1up_off")));
		oneUpAnimations.insert_or_assign(AnimationStates::DEFAULT, std::move(oneUpAnimation));

		mManager.addComponent(oneUpEntity, PhysicsComponent(marginLeft, marginTop, w, h));
		mManager.addComponent(oneUpEntity, AnimationGraphicsComponent(std::move(oneUpAnimations), AnimationStates::DEFAULT));
		mManager.addComponent(oneUpEntity, IdleAnimationComponent());
		mManager.registerEntity(oneUpEntity);
	}

	// Life entities
	{
		int marginLeft = 0;

		for (uint8_t i = 0; i < GameConstants::NUM_STARTING_LIVES; ++i) {
			int life = mManager.createEntity();

			Sprite lifeSprite = std::move(mSpriteRepository.findSprite("capman_life"));
			marginLeft += mMap.singleUnitPixels();
			int marginTop = (mMap.rows() - 1) * mMap.singleUnitPixels();
			int w = lifeSprite.width() * mMap.scaleMultiplier();
			int h = lifeSprite.height() * mMap.scaleMultiplier();

			std::unordered_map<int, Animation> lifeAnimations;
			Animation lifeAnimation;
			lifeAnimation.addSprite(std::move(lifeSprite));
			lifeAnimations.insert_or_assign(AnimationStates::DEFAULT, std::move(lifeAnimation));

			mManager.addComponent(life, PhysicsComponent(marginLeft, marginTop, w, h));
			mManager.addComponent(life, AnimationGraphicsComponent(std::move(lifeAnimations), AnimationStates::DEFAULT));
			mManager.addComponent(life, IdleAnimationComponent());
			mManager.registerEntity(life);

			mLifeEntities.push(life);
		}
	}

	// Cherry in bottom right of map
	{
		int cherry = mManager.createEntity();

		Sprite cherrySprite = std::move(mSpriteRepository.findSprite("cherry"));
		int marginLeft = (mMap.columns() - 2) * mMap.singleUnitPixels();
		int marginTop = (mMap.rows() - 1) * mMap.singleUnitPixels();
		int w = cherrySprite.width() * mMap.scaleMultiplier();
		int h = cherrySprite.height() * mMap.scaleMultiplier();

		std::unordered_map<int, Animation> cherryAnimations;
		Animation cherryAnimation;
		cherryAnimation.addSprite(std::move(cherrySprite));
		cherryAnimations.insert_or_assign(AnimationStates::DEFAULT, std::move(cherryAnimation));

		mManager.addComponent(cherry, PhysicsComponent(marginLeft, marginTop, w, h));
		mManager.addComponent(cherry, AnimationGraphicsComponent(std::move(cherryAnimations), AnimationStates::DEFAULT));
		mManager.addComponent(cherry, IdleAnimationComponent());
		mManager.registerEntity(cherry);
	}

	return true;
}
