#include <MainSystem.h>

MainSystem::MainSystem() {
  internal_state = 0;
  wait_time = 2000;
  LOG->I(TAG, "MainSystem initialized.");
}

void MainSystem::start() {
  switch (internal_state) {
    case IDLE:
    case STOPPED:
      LOG->I(TAG,
             "Changed internal_state " + String(internal_state) + " to 1.");
      internal_state = RUNNING;
      run();
      break;
    case RUNNING:
      LOG->E(TAG,
             "Start called when system was running, stopping function call to "
             "avoid unneeded recursion.");
      break;
    case PAUSED:
      LOG->E(TAG, "System is paused, can't restart system.");
      break;
  }
}

void MainSystem::run() {
  while (internal_state == RUNNING) {
    smm->nextState();
    command->readCommand();
    delay(wait_time);
  }
}

void MainSystem::stop() {
  // Don't need implementation yet
}

void MainSystem::resume() {
  // Don't need implementation yet
}

MainSystem *MainSystem::instance = 0;

MainSystem *MainSystem::getInstance() {
  if (!instance) instance = new MainSystem();
  return instance;
}