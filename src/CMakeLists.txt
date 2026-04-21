set(TARGET_NAME main)
set(SOURCES main.cpp
        Sample/Systems/MovementSystem.cpp
        Sample/Systems/MovementSystem.h
        Sample/Systems/InitSystem.cpp
        Sample/Systems/InitSystem.h
        Sample/Components/PositionComponent.h
        Sample/Components/MovementComponent.h
        Sample/Components/BoxColliderComponent.h
        Sample/Components/CircleColliderComponent.h
        Sample/Components/CollisionComponent.h
        Sample/Components/SpriteComponent.h
        Sample/Components/ShooterComponent.h
        Sample/Components/BulletComponent.h
        Sample/Components/AsteroidComponent.h
        Sample/Systems/InputSystem.cpp
        Sample/Systems/InputSystem.h
        Sample/Systems/CollisionSystem.cpp
        Sample/Systems/CollisionSystem.h
        Sample/Systems/CollisionResolveSystem.cpp
        Sample/Systems/CollisionResolveSystem.h
        Sample/Systems/AsteroidSpawnSystem.cpp
        Sample/Systems/AsteroidSpawnSystem.h
        Sample/Systems/RenderSystem.cpp
        Sample/Systems/RenderSystem.h
        Sample/Systems/ShootingSystem.cpp
        Sample/Systems/ShootingSystem.h
        Sample/Systems/EntityFactory.cpp
        Sample/Systems/EntityFactory.h
        Sample/Systems/BoundariesSystem.cpp
        Sample/Systems/BoundariesSystem.h
        Sample/Components/MoveInputEvent.h
        Sample/Components/ShootEvent.h
        Ecs/Window/Window.cpp
        UI/Text.cpp
        Ecs/Managers/ScoreManager.cpp
        Ecs/Managers/RestartManager.cpp
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

#target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC easy_ecs)
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/Sample
    ${CMAKE_CURRENT_SOURCE_DIR}/Sample/Systems
    ${CMAKE_CURRENT_SOURCE_DIR}/Sample/Components
)

# Copy resources to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Fonts DESTINATION ${CMAKE_BINARY_DIR})

# Set working directory for debugging
set_target_properties(${TARGET_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
