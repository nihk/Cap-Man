#include "Game.h"
#include "PhysicsComponent.h"
#include "Velocity.h"
#include "VelocityComponent.h"
#include "KeyboardDirectionInputComponent.h"
#include "SpriteGraphicsComponent.h"

bool Game::createEntities() {
	// Cap-Man
	int capMan = mManager.createEntity();

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

	mManager.addComponent(capMan, KeyboardDirectionInputComponent(mKeyboard, Directions::RIGHT));
	mManager.addComponent(capMan, VelocityComponent(velocity, speed));
	mManager.addComponent(capMan, PhysicsComponent(50, 50, mMap.unitPixels(1), mMap.unitPixels(1)));
	mManager.addComponent(capMan, SpriteGraphicsComponent(capManAnimations, AnimationStates::WALK_RIGHT));
	mManager.registerEntity(capMan);

	return true;
}
