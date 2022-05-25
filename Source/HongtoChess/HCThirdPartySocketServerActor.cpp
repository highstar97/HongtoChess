#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Networking.h"
#include "HCThirdPartySocketServerActor.h"
#include <string>

AHCThirdPartySocketServerActor::AHCThirdPartySocketServerActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHCThirdPartySocketServerActor::BeginPlay()
{
	Super::BeginPlay();
	
	Start();
}

void AHCThirdPartySocketServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMessage();
}

void AHCThirdPartySocketServerActor::Start()
{
	FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	if (!Socket)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to Making Socket"));
	}

	FIPv4Address ip(211, 211, 7, 124);
	int32 port = 1234;

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(1234);

	bool connected = Socket->Connect(*addr);
	if (!connected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to Connect!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Success to Connect!"));
		ConnectionSocket = Socket;
	}

	FString VarFetch = TEXT("fromjjh");
	TCHAR* VarFetchChar = VarFetch.GetCharArray().GetData();
	int32 size = FCString::Strlen(VarFetchChar);
	int32 sent = 0;

	bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(VarFetchChar), size, sent);
	if (!successful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to send message"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Success to send message"));
	}
}

void AHCThirdPartySocketServerActor::GetMessage()
{
	TArray<uint8> ReceivedData;

	int32 index = 0;
	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(1, FMath::Min(Size, 65507u));
		int32 Read = 0;
		bool successful = ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		if (!successful)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail to Receive"));
		}
		else
		{
			if (ReceivedData.Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Success to Receive but NULL"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Success to Receive"));
				UE_LOG(LogTemp, Warning, TEXT("ReceivedData.Num == %d"), ReceivedData.Num());
				const std::string cstr(reinterpret_cast<const char*>(ReceivedData.GetData()), ReceivedData.Num());
				FString frameAsFString = cstr.c_str();
				UE_LOG(LogTemp, Warning, TEXT("%s"), *frameAsFString);
			}
		}
	}
}