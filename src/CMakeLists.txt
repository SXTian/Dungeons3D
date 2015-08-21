include_directories (../lib)
include_directories (../lib/include)

#	set names for modules
set (	SOURCE_MAIN
        "GameEngine.h"
        "GameEngine.cpp"
        "WinMain.cpp")
        
set (	SOURCE_MATH
        "Math.h"
        "Matrix.h"
        "Vector.h"
        "Matrix.cpp"
        "MatrixStack.h"
        "MatrixStack.cpp")
        
set (	SOURCE_SYSTEMS
        "BaseSystem.h")
        
        set (	SOURCE_MESSAGING_SYSTEM
                "IEventMessage.h"
                "IEventMessage.cpp"
                "MessagingSystem.h"
                "MessagingSystem.cpp")
                
            set ( SOURCE_EVENT_MESSAGES
                    "MessageKeyboard.h"
                    "MessageMouseClick.h"
                    "MessageMouseMove.h"
                    "MessageMouseWheel.h")
                    
        set (	SOURCE_WINDOWS_SYSTEM
                "WindowSize.h"
                "MousePosition.h"
                "WinSystem.h"
                "WinSystem.cpp")
                
        set (	SOURCE_GRAPHICS_SYSTEM
                "GraphicsSystem.h"
                "GraphicsSystem.cpp")
                
            set (	SOURCE_OPENGL
                    "GLHeaders.h"
                    "OpenGL.h"
                    "OpenGL.cpp")
                    
                    
            set (	SOURCE_SHADERS
                    "ShaderTypes.h"
                    "IShaderManager.h"
                    "IShaderManager.cpp"
                    "ShaderManager.h"
                    "ShaderManager.cpp")
                    
            set (	SOURCE_MESH
                    "Mesh.h")
                    
                set ( SOURCE_MESH_SERIALIZATION
                        "MeshData.h")
                        
                    set ( SOURCE_SIMPLE_SERIALIZER
                            "Loader.h"
                            "Loader.cpp")
                            
                    set ( SOURCE_3DS_SERIALIZER
                            "ChunkNames3DS.h"
                            "Parser3DS.h"
                            "Parser3DS.cpp"
                            "Loader3DS.h"
                            "Loader3DS.cpp")
                    
            set (	SOURCE_CAMERA
                    "Camera.h"
                    "Camera.cpp")
                    
            set ( SOURCE_VIEW
                    "BaseView.h"
                    "BaseView.cpp")
                    
                set ( SOURCE_CAMERA_VIEW
                        "CameraView.h"
                        "CameraView.cpp")
                        
                    set ( SOURCE_PANTHEON_VIEW
                            "PantheonView.h"
                            "PantheonView.cpp")
                            
                    set ( SOURCE_GIMBAL_VIEW
                            "Orientation.h"
                            "Orientation.cpp"
                            "GimbalView.h"
                            "GimbalView.cpp")
                            
                    set ( SOURCE_LIGHTS_VIEW
                            "LightsView.h"
                            "LightsView.cpp")
                    

#	make source hiearchy
source_group (	"Source\\Main" FILES ${SOURCE_MAIN})
source_group (	"Source\\Math" FILES ${SOURCE_MATH})
source_group (	"Source\\Systems" FILES ${SOURCE_SYSTEMS})
source_group (	"Source\\Systems\\Messaging" FILES ${SOURCE_MESSAGING_SYSTEM})
source_group (	"Source\\Systems\\Messaging\\Event Messages" FILES ${SOURCE_EVENT_MESSAGES})
source_group (	"Source\\Systems\\Windows" FILES ${SOURCE_WINDOWS_SYSTEM})
source_group (	"Source\\Systems\\Graphics" FILES ${SOURCE_GRAPHICS_SYSTEM})
source_group (	"Source\\Systems\\Graphics\\OpenGL" FILES ${SOURCE_OPENGL})
source_group (	"Source\\Systems\\Graphics\\Shaders" FILES ${SOURCE_SHADERS})
source_group (	"Source\\Systems\\Graphics\\Mesh" FILES ${SOURCE_MESH})
source_group (	"Source\\Systems\\Graphics\\Mesh\\Serialization Policy" FILES ${SOURCE_MESH_SERIALIZATION})
source_group (	"Source\\Systems\\Graphics\\Mesh\\Serialization Policy\\Simple" FILES ${SOURCE_SIMPLE_SERIALIZER})
source_group (	"Source\\Systems\\Graphics\\Mesh\\Serialization Policy\\3DS" FILES ${SOURCE_3DS_SERIALIZER})
source_group (	"Source\\Systems\\Graphics\\Camera" FILES ${SOURCE_CAMERA})
source_group (	"Source\\Systems\\Graphics\\View" FILES ${SOURCE_VIEW})
source_group (	"Source\\Systems\\Graphics\\View\\Camera View" FILES ${SOURCE_CAMERA_VIEW})
source_group (	"Source\\Systems\\Graphics\\View\\Camera View\\Pantheon" FILES ${SOURCE_PANTHEON_VIEW})
source_group (	"Source\\Systems\\Graphics\\View\\Camera View\\Gimbal" FILES ${SOURCE_GIMBAL_VIEW})
source_group (	"Source\\Systems\\Graphics\\View\\Camera View\\Lights" FILES ${SOURCE_LIGHTS_VIEW})

add_executable (Dungeons3D WIN32    ${SOURCE_MAIN}
                                                            ${SOURCE_MATH}
                                                            ${SOURCE_SYSTEMS}
                                                            ${SOURCE_MESSAGING_SYSTEM}
                                                            ${SOURCE_EVENT_MESSAGES}
                                                            ${SOURCE_WINDOWS_SYSTEM}
                                                            ${SOURCE_GRAPHICS_SYSTEM}
                                                            ${SOURCE_OPENGL}
                                                            ${SOURCE_SHADERS}
                                                            ${SOURCE_MESH}
                                                            ${SOURCE_MESH_SERIALIZATION}
                                                            ${SOURCE_SIMPLE_SERIALIZER}
                                                            ${SOURCE_3DS_SERIALIZER}
                                                            ${SOURCE_CAMERA}
                                                            ${SOURCE_VIEW}
                                                            ${SOURCE_CAMERA_VIEW}
                                                            ${SOURCE_PANTHEON_VIEW}
                                                            ${SOURCE_GIMBAL_VIEW}
                                                            ${SOURCE_LIGHTS_VIEW})
                               
target_link_libraries (Dungeons3D ${CMAKE_SOURCE_DIR}/lib/glew32.lib ${CMAKE_SOURCE_DIR}/lib/glew32s.lib ${CMAKE_SOURCE_DIR}/lib/freeglut.lib)



configure_file (${CMAKE_SOURCE_DIR}/vcxproj.user.in ${CMAKE_BINARY_DIR}/src/Dungeons3D.vcxproj.user @ONLY)
                               