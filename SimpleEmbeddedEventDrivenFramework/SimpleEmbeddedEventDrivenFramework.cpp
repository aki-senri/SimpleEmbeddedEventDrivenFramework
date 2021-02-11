// SimpleEmbeddedEventDrivenFramework.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "SimpleEmbeddedEventDrivenFramework.h"
#include "EventManager.h"


using namespace std;

int main()
{
	EventManager envent;

	envent.Run();
}
