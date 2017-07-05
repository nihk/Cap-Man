#include "Game.h"
#include "PhysicsComponent.h"
#include "Velocity.h"
#include "VelocityComponent.h"
#include "KeyboardDirectionInputComponent.h"
#include "SpriteGraphicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "ColorGraphicsComponent.h"
#include "RetreatComponent.h"

// TODO: Move metadata to XML so this method is less bloated
bool Game::createEntities() {
	// Draw order: walls == pellets == powerups < cap-man < ghosts

	std::vector<int> layout = mMap.layout();

	// Background/walls
	{
		int background = mManager.createEntity();
		std::unordered_map<int, Animation> backgroundAnimations;
		Animation backgroundAnimation;
		backgroundAnimation.addSprite(mSpriteRepository.findSprite("background_walls"));
		backgroundAnimations.insert_or_assign(AnimationStates::DEFAULT, backgroundAnimation);

		mManager.addComponent(background, PhysicsComponent(0, 0, mWindow.width(), mWindow.height()));
		mManager.addComponent(background, SpriteGraphicsComponent(backgroundAnimations, AnimationStates::DEFAULT));
		mManager.registerEntity(background);
	}

	// Pellets
	{
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
			}
		}
	}

	// Powerups
	{
		Sprite powerupAsset = mSpriteRepository.findSprite("powerup");
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
				Animation powerupAnimation;
				powerupAnimation.addSprite(powerupAsset);
				powerupAnimations.insert_or_assign(AnimationStates::DEFAULT, powerupAnimation);
				mManager.addComponent(powerup, SpriteGraphicsComponent(powerupAnimations, AnimationStates::DEFAULT));

				mManager.registerEntity(powerup);
			}
		}
	}

	// Cap-Man
	{
		int capMan = mManager.createEntity();

		// TODO: Don't conflate Directions with AnimationStates
		std::unordered_map<int, Animation> capManAnimations;
		Animation walkLeft(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkLeft.addSprite(mSpriteRepository.findSprite("capman_closed"));
		walkLeft.addSprite(mSpriteRepository.findSprite("capman_left1"));
		walkLeft.addSprite(mSpriteRepository.findSprite("capman_left2"));
		walkLeft.addSprite(mSpriteRepository.findSprite("capman_left1"));
		capManAnimations.insert_or_assign(AnimationStates::WALK_LEFT, walkLeft);
		Animation walkRight(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkRight.addSprite(mSpriteRepository.findSprite("capman_closed"));
		walkRight.addSprite(mSpriteRepository.findSprite("capman_right1"));
		walkRight.addSprite(mSpriteRepository.findSprite("capman_right2"));
		walkRight.addSprite(mSpriteRepository.findSprite("capman_right1"));
		capManAnimations.insert_or_assign(AnimationStates::WALK_RIGHT, walkRight);
		Animation walkUp(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkUp.addSprite(mSpriteRepository.findSprite("capman_closed"));
		walkUp.addSprite(mSpriteRepository.findSprite("capman_up1"));
		walkUp.addSprite(mSpriteRepository.findSprite("capman_up2"));
		walkUp.addSprite(mSpriteRepository.findSprite("capman_up1"));
		capManAnimations.insert_or_assign(AnimationStates::WALK_UP, walkUp);
		Animation walkDown(GameConstants::ANIMATION_FRAME_INTERVAL);
		walkDown.addSprite(mSpriteRepository.findSprite("capman_closed"));
		walkDown.addSprite(mSpriteRepository.findSprite("capman_down1"));
		walkDown.addSprite(mSpriteRepository.findSprite("capman_down2"));
		walkDown.addSprite(mSpriteRepository.findSprite("capman_down1"));
		capManAnimations.insert_or_assign(AnimationStates::WALK_DOWN, walkDown);
		Animation death(GameConstants::ANIMATION_FRAME_INTERVAL);
		death.addSprite(mSpriteRepository.findSprite("capman_death1"));
		death.addSprite(mSpriteRepository.findSprite("capman_death2"));
		death.addSprite(mSpriteRepository.findSprite("capman_death3"));
		death.addSprite(mSpriteRepository.findSprite("capman_death4"));
		death.addSprite(mSpriteRepository.findSprite("capman_death5"));
		death.addSprite(mSpriteRepository.findSprite("capman_death6"));
		death.addSprite(mSpriteRepository.findSprite("capman_death7"));
		death.addSprite(mSpriteRepository.findSprite("capman_death8"));
		death.addSprite(mSpriteRepository.findSprite("capman_death9"));
		death.addSprite(mSpriteRepository.findSprite("capman_death10"));
		death.addSprite(mSpriteRepository.findSprite("capman_death11"));
		capManAnimations.insert_or_assign(AnimationStates::DEATH, death);
		Velocity velocity(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED), 0);
		float speed = static_cast<float>(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED));

		int capManStart = mMap.indexOf(MapLayoutElements::CAP_MAN);
		Point startPoint = mMap.mapLocation(capManStart, true /* scaleUnitsToPixels */);

		// Start Cap-Man off as if a left key were pressed
		mKeyboard.setRecentKeyDown(Keys::LEFT);

		mManager.addComponent(capMan, KeyboardDirectionInputComponent(mKeyboard, Directions::LEFT));
		mManager.addComponent(capMan, VelocityComponent(velocity, speed));
		mManager.addComponent(capMan, PhysicsComponent(startPoint.x(), startPoint.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels()));
		mManager.addComponent(capMan, SpriteGraphicsComponent(capManAnimations, AnimationStates::WALK_LEFT));
		mManager.addComponent(capMan, LastValidDirectionComponent());
		mManager.registerEntity(capMan);
	}

	// Ghosts
	{
		std::vector<std::string> ghostNames = { "inky", "blinky", "pinky", "clyde" };
		for (const auto& ghostName : ghostNames) {

			int ghost = mManager.createEntity();

			std::unordered_map<int, Animation> ghostAnimations;
			Animation walkLeft(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkLeft.addSprite(mSpriteRepository.findSprite(ghostName + "_left1"));
			walkLeft.addSprite(mSpriteRepository.findSprite(ghostName + "_left2"));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_LEFT, walkLeft);
			Animation walkRight(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkRight.addSprite(mSpriteRepository.findSprite(ghostName + "_right1"));
			walkRight.addSprite(mSpriteRepository.findSprite(ghostName + "_right2"));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_RIGHT, walkRight);
			Animation walkUp(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkUp.addSprite(mSpriteRepository.findSprite(ghostName + "_up1"));
			walkUp.addSprite(mSpriteRepository.findSprite(ghostName + "_up2"));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_UP, walkUp);
			Animation walkDown(GameConstants::ANIMATION_FRAME_INTERVAL);
			walkDown.addSprite(mSpriteRepository.findSprite(ghostName + "_down1"));
			walkDown.addSprite(mSpriteRepository.findSprite(ghostName + "_down2"));
			ghostAnimations.insert_or_assign(AnimationStates::WALK_DOWN, walkDown);

			Animation deathLeft;
			deathLeft.addSprite(mSpriteRepository.findSprite("ghost_death_left"));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_LEFT, deathLeft);
			Animation deathRight;
			deathRight.addSprite(mSpriteRepository.findSprite("ghost_death_right"));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_RIGHT, deathRight);
			Animation deathUp;
			deathUp.addSprite(mSpriteRepository.findSprite("ghost_death_up"));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_UP, deathUp);
			Animation deathDown;
			deathDown.addSprite(mSpriteRepository.findSprite("ghost_death_down"));
			ghostAnimations.insert_or_assign(AnimationStates::DEATH_DOWN, deathDown);

			Animation vulnerable(GameConstants::ANIMATION_FRAME_INTERVAL);
			vulnerable.addSprite(mSpriteRepository.findSprite("ghost_blue1"));
			vulnerable.addSprite(mSpriteRepository.findSprite("ghost_blue2"));
			ghostAnimations.insert_or_assign(AnimationStates::VULNERABLE, deathDown);
			// TODO: most to constant
			// TODO: vulnetable expiring faster?
			Animation vulnerableExpiring(264 /* millis */);
			vulnerableExpiring.addSprite(mSpriteRepository.findSprite("ghost_blue1"));
			vulnerableExpiring.addSprite(mSpriteRepository.findSprite("ghost_white1"));
			vulnerableExpiring.addSprite(mSpriteRepository.findSprite("ghost_blue2"));
			vulnerableExpiring.addSprite(mSpriteRepository.findSprite("ghost_white2"));
			ghostAnimations.insert_or_assign(AnimationStates::VULNERABLE_EXPIRING, vulnerableExpiring);

			// TODO: set initial velocity
			Velocity velocity;
			float speed = static_cast<float>(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED));

			int ghostStart;

			// TODO: Refactor. Perhaps indexOf takes a string?
			if (ghostName == ghostNames.at(0)) {
				ghostStart = mMap.indexOf(MapLayoutElements::INKY);
			} else if (ghostName == ghostNames.at(1)) {
				ghostStart = mMap.indexOf(MapLayoutElements::BLINKY);
			} else if (ghostName == ghostNames.at(2)) {
				ghostStart = mMap.indexOf(MapLayoutElements::PINKY);
			} else {
				ghostStart = mMap.indexOf(MapLayoutElements::CLYDE);
			}

			Point startPoint = mMap.mapLocation(ghostStart, true /* scaleUnitsToPixels */);

			// TODO: incorporate Ghost input component
			mManager.addComponent(ghost, RetreatComponent(mMap));
			mManager.addComponent(ghost, VelocityComponent(velocity, speed));
			mManager.addComponent(ghost, PhysicsComponent(startPoint.x(), startPoint.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels()));
			mManager.addComponent(ghost, SpriteGraphicsComponent(ghostAnimations, AnimationStates::WALK_LEFT));
			mManager.addComponent(ghost, LastValidDirectionComponent());
			mManager.registerEntity(ghost);
		}
	}

	return true;
}
