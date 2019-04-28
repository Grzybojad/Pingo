cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(Pingo)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Pingo")
set(SHORT_NAME Pingo)
set(VITA_TITLEID  "GRZB00003")
set(VITA_VERSION  "01.10")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

include_directories(
	../common
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${VITA_APP_NAME}
  src/main.cpp
  src/game.hpp
  src/game.cpp
  src/ball.hpp
  src/ball.cpp
  src/debug.hpp
  src/debug.cpp
  src/gui.hpp
  src/gui.cpp
  src/level.hpp
  src/level.cpp
  src/input.hpp
  src/input.cpp
  src/menu.hpp
  src/menu.cpp
  src/timer.hpp
  src/timer.cpp
  src/texture.hpp
  src/texture.cpp
  src/sound.hpp
  src/sound.cpp
  src/common.hpp
  src/common.cpp
)

target_link_libraries(${VITA_APP_NAME}
  SceLibKernel_stub
  SceDisplay_stub
  SceTouch_stub
  SceAudio_stub
  -lvita2d 
  -lSceDisplay_stub 
  -lSceGxm_stub
  -lSceSysmodule_stub
  -lSceCtrl_stub
  -lScePgf_stub
  -lScePvf_stub
  -lSceCommonDialog_stub
  -lfreetype
  -lpng
  -ljpeg
  -lz
  -lm
  -lc
  soloud
  pthread
  m
)

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME})
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  
  # Livearea files
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg0.png sce_sys/livearea/contents/bg0.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

  # Font
  #FILE font/Ubuntu-Medium.ttf  font/Ubuntu-Medium.ttf
  FILE font/ConcertOne-Regular.ttf  font/ConcertOne-Regular.ttf

  # Textures
  FILE img/level/wall.png          img/level/wall.png
  FILE img/level/floorBlank.png    img/level/floorBlank.png
  FILE img/level/floorPainted.png  img/level/floorPainted.png
  FILE img/level/ball.png          img/level/ball.png

  FILE img/common/background1.png  img/common/background1.png
  FILE img/common/background2.png  img/common/background2.png
  FILE img/common/background3.png  img/common/background3.png
  FILE img/common/star.png         img/common/star.png
  FILE img/common/messageBox.png   img/common/messageBox.png

  FILE img/menu/logo.png                  img/menu/logo.png
  FILE img/menu/startButton.png           img/menu/startButton.png
  FILE img/menu/startSelected.png         img/menu/startSelected.png
  FILE img/menu/levelSelectButton.png     img/menu/levelSelectButton.png
  FILE img/menu/levelSelectSelected.png   img/menu/levelSelectSelected.png
  FILE img/menu/optionsButton.png         img/menu/optionsButton.png
  FILE img/menu/optionsSelected.png       img/menu/optionsSelected.png

  FILE img/menu/doorOpened.png        img/menu/doorOpened.png
  FILE img/menu/doorClosed.png        img/menu/doorClosed.png
  FILE img/menu/doorLocked.png        img/menu/doorLocked.png
  FILE img/menu/doorLockedOutline.png img/menu/doorLockedOutline.png
  FILE img/menu/doorStar1.png         img/menu/doorStar1.png
  FILE img/menu/doorStar2.png         img/menu/doorStar2.png
  FILE img/menu/doorStar3.png         img/menu/doorStar3.png
  FILE img/menu/doorPlatform.png      img/menu/doorPlatform.png

  FILE img/menu/lf-levelComplete.png      img/menu/lf-levelComplete.png
  FILE img/menu/lf-nextLevel.png          img/menu/lf-nextLevel.png
  FILE img/menu/lf-nextLevelSelected.png  img/menu/lf-nextLevelSelected.png
  FILE img/menu/lf-restart.png            img/menu/lf-restart.png
  FILE img/menu/lf-restartSelected.png    img/menu/lf-restartSelected.png
  FILE img/menu/lf-menu.png               img/menu/lf-menu.png
  FILE img/menu/lf-menuSelected.png       img/menu/lf-menuSelected.png

  FILE img/menu/pause/pausedText.png      img/menu/pause/pausedText.png
  FILE img/menu/pause/return.png          img/menu/pause/return.png
  FILE img/menu/pause/returnSelected.png  img/menu/pause/returnSelected.png
  FILE img/menu/pause/restart.png         img/menu/pause/restart.png
  FILE img/menu/pause/restartSelected.png img/menu/pause/restartSelected.png
  FILE img/menu/pause/menu.png            img/menu/pause/menu.png
  FILE img/menu/pause/menuSelected.png    img/menu/pause/menuSelected.png

  FILE img/menu/underConstruction.png     img/menu/underConstruction.png


  # Sound effects
  FILE sounds/ballHit.ogg        sounds/ballHit.ogg
  FILE sounds/menuMove.wav       sounds/menuMove.wav
  FILE sounds/levelFinish.wav    sounds/levelFinish.wav


  # Levels
  # Figure out how to load all levels from file automatically
  FILE levels/level001.txt       levels/level001.txt
  FILE levels/level002.txt       levels/level002.txt
  FILE levels/level003.txt       levels/level003.txt
  FILE levels/level004.txt       levels/level004.txt
  FILE levels/level005.txt       levels/level005.txt
  FILE levels/level006.txt       levels/level006.txt
  FILE levels/level007.txt       levels/level007.txt
  FILE levels/level008.txt       levels/level008.txt
  FILE levels/level009.txt       levels/level009.txt
  FILE levels/level010.txt       levels/level010.txt
  FILE levels/level011.txt       levels/level011.txt
  FILE levels/level012.txt       levels/level012.txt
  FILE levels/level013.txt       levels/level013.txt
  FILE levels/level014.txt       levels/level014.txt
  FILE levels/level015.txt       levels/level015.txt
  FILE levels/level016.txt       levels/level016.txt
  FILE levels/level017.txt       levels/level017.txt
  FILE levels/level018.txt       levels/level018.txt
  FILE levels/level019.txt       levels/level019.txt
  FILE levels/level020.txt       levels/level020.txt
  FILE levels/level021.txt       levels/level021.txt
  FILE levels/level022.txt       levels/level022.txt
  FILE levels/level023.txt       levels/level023.txt
  FILE levels/level024.txt       levels/level024.txt
  FILE levels/level025.txt       levels/level025.txt
  FILE levels/level026.txt       levels/level026.txt
  FILE levels/level027.txt       levels/level027.txt
  FILE levels/level028.txt       levels/level028.txt
  FILE levels/level029.txt       levels/level029.txt
  FILE levels/level030.txt       levels/level030.txt
)

