#include "SKSE/Interfaces.h"
#include "Logging.h"
#include "Events.h"
#include "Utility.h"

void Listener(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Events::OnSpellCastEventHandler::Register();
        Events::OnObjectLoadedEventHandler::Register();
        Utility::InitFormCache();
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLogging();
    const auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();
    logger::info("{} {} is loading...", plugin->GetName(), version);
    Init(skse);

    if (const auto messaging = SKSE::GetMessagingInterface();
        !messaging->RegisterListener(Listener)) return false;

    logger::info("{} has finished loading.", plugin->GetName());
    return true;
}
