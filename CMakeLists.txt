cmake_minimum_required(VERSION "3.3")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(horgand VERSION "1.14" LANGUAGES C CXX)
set(PROJECT_WEBSITE "https://github.com/linuxmao-org/horgand")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD "11")

include(GNUWarnings)
enable_gnu_warning("all")

include(FindPkgConfig)

add_executable(horgand
  "src/HORGAN.cxx"
  "src/jackoutput.C"
  "src/main.C"
  "src/organAccompaniment.C"
  "src/organAudioOut.C"
  "src/organ.C"
  "src/organDSPEffects.C"
  "src/organFileIO.C"
  "src/organMIDIIn.C"
  "src/organvarios.C")
target_compile_options(horgand
  PRIVATE "")
target_compile_definitions(horgand
  PRIVATE "PACKAGE=\"${PROJECT_NAME}\""
  PRIVATE "VERSION=\"${PROJECT_VERSION}\""
  PRIVATE "WEBSITE=\"${PROJECT_WEBSITE}\""
  PRIVATE "DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\"")

#
find_package(Threads REQUIRED)
target_link_libraries(horgand
  PRIVATE ${CMAKE_THREAD_LIBS_INIT})

#
set(FLTK_SKIP_OPENGL TRUE)
set(FLTK_SKIP_FORMS TRUE)
set(FLTK_SKIP_IMAGES TRUE)
find_package(FLTK REQUIRED)
target_include_directories(horgand
  PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(horgand
  PRIVATE ${FLTK_LIBRARIES})

#
pkg_check_modules(XPM "xpm" REQUIRED)
target_include_directories(horgand
  PRIVATE ${XPM_INCLUDE_DIRS})
target_link_libraries(horgand
  PRIVATE ${XPM_LIBRARIES})

#
pkg_check_modules(JACK "jack" REQUIRED)
pkg_check_modules(ALSA "alsa" REQUIRED)
pkg_check_modules(SNDFILE "sndfile" REQUIRED)
target_include_directories(horgand
  PRIVATE ${JACK_INCLUDE_DIRS}
  PRIVATE ${ALSA_INCLUDE_DIRS}
  PRIVATE ${SNDFILE_INCLUDE_DIRS})
target_link_libraries(horgand
  PRIVATE ${JACK_LIBRARIES}
  PRIVATE ${ALSA_LIBRARIES}
  PRIVATE ${SNDFILE_LIBRARIES})

#
install(TARGETS horgand
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(FILES
  "data/Default.horeb"
  "data/Rhythm_List.txt"
  "data/130_Houseloop_2.wav"
  "data/AcousticBass.wav"
  "data/crackle_loop01.wav"
  "data/egg_loop01.wav"
  "data/FenderBass.wav"
  "data/FretlessBass.wav"
  "data/frog_loop01.wav"
  "data/funkyfeet1.wav"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")

install(FILES
  "man/horgand.1"
  DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
