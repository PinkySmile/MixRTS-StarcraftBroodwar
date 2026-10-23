cmake_minimum_required(VERSION 4.1)
project(MixRTS_SCBW)

set(CMAKE_CXX_STANDARD 20)

add_library(
	scbw_ui MODULE
	ui/src/D2KCameo.cpp
	ui/src/D2KCameo.hpp
	ui/src/SCBWUI.cpp
	ui/src/SCBWUI.hpp
	ui/src/main.cpp
)
target_link_libraries(
	scbw_ui
	MixRTS_Core
)

add_library(
	scbw_support_powers MODULE
	src/main.cpp
)
target_link_libraries(
	scbw_support_powers
	MixRTS_Core
)

set(SCBW_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Scanning ${SCBW_SOURCE_DIR}")
file(GLOB_RECURSE SCBW_ASSET_FILES CONFIGURE_DEPENDS
	"${SCBW_SOURCE_DIR}/*.png"
	"${SCBW_SOURCE_DIR}/*.ogg"
	"${SCBW_SOURCE_DIR}/*.json"
	"${SCBW_SOURCE_DIR}/*.dat"
	"${SCBW_SOURCE_DIR}/*.gui"
	"${SCBW_SOURCE_DIR}/*.BMP"
)

set(COPIED_FILES "")
message(STATUS "Install in ${MOD_DEST_PATH}")
foreach(SCBW_ASSET_PATH ${SCBW_ASSET_FILES})
	get_filename_component(FILE_NAME ${SCBW_ASSET_PATH} NAME)
	cmake_path(RELATIVE_PATH SCBW_ASSET_PATH BASE_DIRECTORY ${SCBW_SOURCE_DIR} OUTPUT_VARIABLE SCBW_ASSET_PATH_REL)

	add_custom_command(
		OUTPUT "${MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SCBW_ASSET_PATH}" "${MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}"
		DEPENDS "${SCBW_ASSET_PATH}"
		COMMENT "Copy SCBW:${SCBW_ASSET_PATH_REL}"
	)
	list(APPEND COPIED_FILES "${MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}")
endforeach()

# Target that drives the build dependencies
add_custom_target(scbw_assets ALL DEPENDS ${COPIED_FILES})
add_dependencies(scbw_ui scbw_assets)
add_dependencies(scbw_support_powers scbw_assets)

add_custom_command(
	OUTPUT "${MOD_DEST_PATH}/ui/ui.ui"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:scbw_ui> "${MOD_DEST_PATH}/ui/ui.ui"
	DEPENDS $<TARGET_FILE:scbw_ui>
	COMMENT "Copy SCBW:ui/ui.ui"
)
add_custom_command(
	OUTPUT "${MOD_DEST_PATH}/support.dl"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:scbw_support_powers> "${MOD_DEST_PATH}/support.dl"
	DEPENDS $<TARGET_FILE:scbw_support_powers>
	COMMENT "Copy SCBW:support.dl"
)

add_custom_target(starcraft_broodwar ALL DEPENDS "${MOD_DEST_PATH}/ui/ui.ui" "${MOD_DEST_PATH}/support.dl")
add_dependencies(starcraft_broodwar scbw_ui)
add_dependencies(starcraft_broodwar scbw_support_powers)

if (NOT NO_TEST)
	add_library(
		scbw_ui_test MODULE
		ui/src/D2KCameo.cpp
		ui/src/D2KCameo.hpp
		ui/src/SCBWUI.cpp
		ui/src/SCBWUI.hpp
		ui/src/main.cpp
	)
	target_link_libraries(
		scbw_ui_test
		MixRTS_Core_Mock
	)

	add_library(
		scbw_support_powers_test MODULE
		src/main.cpp
	)
	target_link_libraries(
		scbw_support_powers_test
		MixRTS_Core_Mock
	)

	set(COPIED_FILES "")
	message(STATUS "Install in ${TEST_MOD_DEST_PATH}")
	foreach(SCBW_ASSET_PATH ${SCBW_ASSET_FILES})
		get_filename_component(FILE_NAME ${SCBW_ASSET_PATH} NAME)
		cmake_path(RELATIVE_PATH SCBW_ASSET_PATH BASE_DIRECTORY ${SCBW_SOURCE_DIR} OUTPUT_VARIABLE SCBW_ASSET_PATH_REL)

		add_custom_command(
			OUTPUT "${TEST_MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}"
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SCBW_ASSET_PATH}" "${TEST_MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}"
			DEPENDS "${SCBW_ASSET_PATH}"
			COMMENT "Copy TEST_SCBW:${SCBW_ASSET_PATH_REL}"
		)
		list(APPEND COPIED_FILES "${TEST_MOD_DEST_PATH}/${SCBW_ASSET_PATH_REL}")
	endforeach()

	# Target that drives the build dependencies
	add_custom_target(scbw_assets_test ALL DEPENDS ${COPIED_FILES})
	add_dependencies(scbw_ui_test scbw_assets_test)
	add_dependencies(scbw_support_powers_test scbw_assets_test)

	add_custom_command(
		OUTPUT "${TEST_MOD_DEST_PATH}/ui/ui.ui"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:scbw_ui> "${TEST_MOD_DEST_PATH}/ui/ui.ui"
		DEPENDS $<TARGET_FILE:scbw_ui>
		COMMENT "Copy TEST_SCBW:ui/ui.ui"
	)
	add_custom_command(
		OUTPUT "${TEST_MOD_DEST_PATH}/support.dl"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:scbw_support_powers> "${TEST_MOD_DEST_PATH}/support.dl"
		DEPENDS $<TARGET_FILE:scbw_support_powers>
		COMMENT "Copy TEST_SCBW:support.dl"
	)

	add_custom_target(
		starcraft_broodwar_test ALL DEPENDS
		"${TEST_MOD_DEST_PATH}/ui/ui.ui"
		"${TEST_MOD_DEST_PATH}/support.dl"
	)
	add_dependencies(starcraft_broodwar_test scbw_ui_test scbw_support_powers_test)
endif ()
