# CMakeList.txt : SimpleEmbeddedEventDrivenFramework の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

include_directories(common)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (SimpleEmbeddedEventDrivenFramework "SimpleEmbeddedEventDrivenFramework.cpp" "SimpleEmbeddedEventDrivenFramework.h" "common/EventManager.cpp" "common/EventManager.h" "common/EventQueue.cpp" "common/EventQueue.h"  "common/TCPClient.cpp" "common/TCPClient.h" "common/Timer.h" "common/Timer.cpp" "common/TCPServer.h" "common/TCPServer.cpp"   "common/KeyValueConfig.cpp" "common/Logger.h" "common/Logger.cpp")

if(WIN32)
  target_link_libraries(SimpleEmbeddedEventDrivenFramework ws2_32 wsock32)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
