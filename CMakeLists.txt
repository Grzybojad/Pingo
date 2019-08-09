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
  src/stats.hpp
  src/stats.cpp
  src/credits.hpp
  src/credits.cpp
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
  FILE img/level/wall.png             img/level/wall.png
  FILE img/level/floorBlank.png       img/level/floorBlank.png
  FILE img/level/floorPainted.png     img/level/floorPainted.png
  FILE img/level/ball.png             img/level/ball.png
  FILE img/level/wallFill.png         img/level/wallFill.png
  FILE img/level/stopTile.png         img/level/stopTile.png
  FILE img/level/paintBlob.png        img/level/paintBlob.png
  FILE img/level/floorEmpty.png       img/level/floorEmpty.png
  FILE img/level/conveyorBlank.png    img/level/conveyorBlank.png
  FILE img/level/conveyorPainted.png  img/level/conveyorPainted.png

  FILE img/level/pause.png            img/level/pause.png
  FILE img/level/restart.png          img/level/restart.png

  FILE img/common/background1.png  img/common/background1.png
  FILE img/common/background2.png  img/common/background2.png
  FILE img/common/background3.png  img/common/background3.png
  FILE img/common/background4.png  img/common/background4.png
  FILE img/common/star.png         img/common/star.png
  FILE img/common/messageBox.png   img/common/messageBox.png
  FILE img/common/back.png         img/common/back.png

  FILE img/menu/main/logo.png                  img/menu/main/logo.png
  FILE img/menu/main/startButton.png           img/menu/main/startButton.png
  FILE img/menu/main/startSelected.png         img/menu/main/startSelected.png
  FILE img/menu/main/levelSelectButton.png     img/menu/main/levelSelectButton.png
  FILE img/menu/main/levelSelectSelected.png   img/menu/main/levelSelectSelected.png
  FILE img/menu/main/optionsButton.png         img/menu/main/optionsButton.png
  FILE img/menu/main/optionsSelected.png       img/menu/main/optionsSelected.png

  FILE img/menu/levelSelect/doorOpened.png        img/menu/levelSelect/doorOpened.png
  FILE img/menu/levelSelect/doorClosed.png        img/menu/levelSelect/doorClosed.png
  FILE img/menu/levelSelect/doorLocked.png        img/menu/levelSelect/doorLocked.png
  FILE img/menu/levelSelect/doorLockedOutline.png img/menu/levelSelect/doorLockedOutline.png
  FILE img/menu/levelSelect/doorPlatform.png      img/menu/levelSelect/doorPlatform.png
  FILE img/menu/levelSelect/headerWorld.png       img/menu/levelSelect/headerWorld.png
  FILE img/menu/levelSelect/header1.png           img/menu/levelSelect/header1.png
  FILE img/menu/levelSelect/header2.png           img/menu/levelSelect/header2.png
  FILE img/menu/levelSelect/lTrigger.png              img/menu/levelSelect/lTrigger.png
  FILE img/menu/levelSelect/rTrigger.png              img/menu/levelSelect/rTrigger.png

  FILE img/menu/levelFinish/lf-levelComplete.png      img/menu/levelFinish/lf-levelComplete.png
  FILE img/menu/levelFinish/lf-nextLevel.png          img/menu/levelFinish/lf-nextLevel.png
  FILE img/menu/levelFinish/lf-nextLevelSelected.png  img/menu/levelFinish/lf-nextLevelSelected.png
  FILE img/menu/levelFinish/lf-restart.png            img/menu/levelFinish/lf-restart.png
  FILE img/menu/levelFinish/lf-restartSelected.png    img/menu/levelFinish/lf-restartSelected.png
  FILE img/menu/levelFinish/lf-menu.png               img/menu/levelFinish/lf-menu.png
  FILE img/menu/levelFinish/lf-menuSelected.png       img/menu/levelFinish/lf-menuSelected.png

  FILE img/menu/pause/pausedText.png      img/menu/pause/pausedText.png
  FILE img/menu/pause/return.png          img/menu/pause/return.png
  FILE img/menu/pause/returnSelected.png  img/menu/pause/returnSelected.png
  FILE img/menu/pause/restart.png         img/menu/pause/restart.png
  FILE img/menu/pause/restartSelected.png img/menu/pause/restartSelected.png
  FILE img/menu/pause/menu.png            img/menu/pause/menu.png
  FILE img/menu/pause/menuSelected.png    img/menu/pause/menuSelected.png

  FILE img/menu/options/header.png        img/menu/options/header.png
  FILE img/menu/options/music.png         img/menu/options/music.png
  FILE img/menu/options/music_on.png      img/menu/options/music_on.png
  FILE img/menu/options/sfx.png           img/menu/options/sfx.png
  FILE img/menu/options/sfx_on.png        img/menu/options/sfx_on.png
  FILE img/menu/options/touch.png         img/menu/options/touch.png
  FILE img/menu/options/touch_on.png      img/menu/options/touch_on.png
  FILE img/menu/options/stats.png         img/menu/options/stats.png
  FILE img/menu/options/checkbox_off.png  img/menu/options/checkbox_off.png
  FILE img/menu/options/checkbox_on.png   img/menu/options/checkbox_on.png
  FILE img/menu/options/slider_off.png    img/menu/options/slider_off.png
  FILE img/menu/options/slider_on.png     img/menu/options/slider_on.png

  FILE img/menu/underConstruction.png     img/menu/underConstruction.png


  # Sound effects
  FILE sounds/ballHit.ogg        sounds/ballHit.ogg
  FILE sounds/menuMove.wav       sounds/menuMove.wav
  FILE sounds/levelFinish.wav    sounds/levelFinish.wav

  FILE sounds/Good-Morning-Doctor-Weird.ogg      sounds/Good-Morning-Doctor-Weird.ogg
  FILE sounds/Puzzle-Dreams-3.ogg                sounds/Puzzle-Dreams-3.ogg
  FILE sounds/Puzzle-Caves.ogg                   sounds/Puzzle-Caves.ogg
  FILE sounds/Hypnotic-Puzzle3.ogg               sounds/Hypnotic-Puzzle3.ogg
  FILE sounds/Rubiks-Dodecahedron.ogg            sounds/Rubiks-Dodecahedron.ogg
  FILE sounds/8-Bit-Puzzler.ogg                  sounds/8-Bit-Puzzler.ogg

  FILE sounds/Air-lock.ogg                       sounds/Air-lock.ogg


  # Levels
  FILE levels/World1/level001.txt       levels/World1/level001.txt
  FILE levels/World1/level002.txt       levels/World1/level002.txt
  FILE levels/World1/level003.txt       levels/World1/level003.txt
  FILE levels/World1/level004.txt       levels/World1/level004.txt
  FILE levels/World1/level005.txt       levels/World1/level005.txt
  FILE levels/World1/level006.txt       levels/World1/level006.txt
  FILE levels/World1/level007.txt       levels/World1/level007.txt
  FILE levels/World1/level008.txt       levels/World1/level008.txt
  FILE levels/World1/level009.txt       levels/World1/level009.txt
  FILE levels/World1/level010.txt       levels/World1/level010.txt
  FILE levels/World1/level011.txt       levels/World1/level011.txt
  FILE levels/World1/level012.txt       levels/World1/level012.txt
  FILE levels/World1/level013.txt       levels/World1/level013.txt
  FILE levels/World1/level014.txt       levels/World1/level014.txt
  FILE levels/World1/level015.txt       levels/World1/level015.txt
  FILE levels/World1/level016.txt       levels/World1/level016.txt
  FILE levels/World1/level017.txt       levels/World1/level017.txt
  FILE levels/World1/level018.txt       levels/World1/level018.txt
  FILE levels/World1/level019.txt       levels/World1/level019.txt
  FILE levels/World1/level020.txt       levels/World1/level020.txt
  FILE levels/World1/level021.txt       levels/World1/level021.txt
  FILE levels/World1/level022.txt       levels/World1/level022.txt
  FILE levels/World1/level023.txt       levels/World1/level023.txt
  FILE levels/World1/level024.txt       levels/World1/level024.txt
  FILE levels/World1/level025.txt       levels/World1/level025.txt
  FILE levels/World1/level026.txt       levels/World1/level026.txt
  FILE levels/World1/level027.txt       levels/World1/level027.txt
  FILE levels/World1/level028.txt       levels/World1/level028.txt
  FILE levels/World1/level029.txt       levels/World1/level029.txt
  FILE levels/World1/level030.txt       levels/World1/level030.txt

  FILE levels/World2/level001.txt       levels/World2/level001.txt
  FILE levels/World2/level002.txt       levels/World2/level002.txt
  FILE levels/World2/level003.txt       levels/World2/level003.txt
  FILE levels/World2/level004.txt       levels/World2/level004.txt
  FILE levels/World2/level005.txt       levels/World2/level005.txt
  FILE levels/World2/level006.txt       levels/World2/level006.txt
  FILE levels/World2/level007.txt       levels/World2/level007.txt
  FILE levels/World2/level008.txt       levels/World2/level008.txt
  FILE levels/World2/level009.txt       levels/World2/level009.txt
  FILE levels/World2/level010.txt       levels/World2/level010.txt
  FILE levels/World2/level011.txt       levels/World2/level011.txt
  FILE levels/World2/level012.txt       levels/World2/level012.txt
  FILE levels/World2/level013.txt       levels/World2/level013.txt
  FILE levels/World2/level014.txt       levels/World2/level014.txt
  FILE levels/World2/level015.txt       levels/World2/level015.txt
  FILE levels/World2/level016.txt       levels/World2/level016.txt
  FILE levels/World2/level017.txt       levels/World2/level017.txt
  FILE levels/World2/level018.txt       levels/World2/level018.txt
  FILE levels/World2/level019.txt       levels/World2/level019.txt
  FILE levels/World2/level020.txt       levels/World2/level020.txt
  FILE levels/World2/level021.txt       levels/World2/level021.txt
  FILE levels/World2/level022.txt       levels/World2/level022.txt
  FILE levels/World2/level023.txt       levels/World2/level023.txt
  FILE levels/World2/level024.txt       levels/World2/level024.txt
  FILE levels/World2/level025.txt       levels/World2/level025.txt
  FILE levels/World2/level026.txt       levels/World2/level026.txt
  FILE levels/World2/level027.txt       levels/World2/level027.txt
  FILE levels/World2/level028.txt       levels/World2/level028.txt
  FILE levels/World2/level029.txt       levels/World2/level029.txt
  FILE levels/World2/level030.txt       levels/World2/level030.txt
)

