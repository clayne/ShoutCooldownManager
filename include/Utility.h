#pragma once
#include "RE/A/Actor.h"

class Utility {
protected:
    Utility() = default;
    ~Utility() = default;

public:
    Utility(const Utility&) = delete; // Prevent copy construction
    Utility(Utility&&) = delete; // Prevent move construction
    Utility& operator=(const Utility&) = delete; // Prevent copy assignment
    Utility& operator=(Utility&&) = delete; // Prevent move assignment

    static Utility* GetSingleton() {
        static Utility singleton;
        return std::addressof(singleton);
    }

    using CacheType = std::unordered_map<RE::TESShout*, std::chrono::time_point<std::chrono::system_clock>>;
    inline static std::unordered_map<RE::Actor*, CacheType> actor_shout_cooldown_map;

    inline static std::unordered_set<RE::TESShout*> shouts;

    static void InitFormCache() {
        const auto handler = RE::TESDataHandler::GetSingleton();

        // Base game - Shouts
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x13E07, "Skyrim.esm"sv));     // Unrelenting Force
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x2F7BA, "Skyrim.esm"sv));     // Whirlwind Sprint
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x32920, "Skyrim.esm"sv));     // Become Ethereal
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x32921, "Skyrim.esm"sv));     // Elemental Fury
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x3CD34, "Skyrim.esm"sv));     // Clear Skies
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x3F9EA, "Skyrim.esm"sv));     // Fire Breath
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x44250, "Skyrim.esm"sv));     // Dragonrend
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x46B8C, "Skyrim.esm"sv));     // Call Dragon
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x48AC9, "Skyrim.esm"sv));     // Slow Time
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x5196A, "Skyrim.esm"sv));     // Call of Valor
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x5D16B, "Skyrim.esm"sv));     // Frost Breath
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x5FC77, "Skyrim.esm"sv));     // Animal Ally
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7097B, "Skyrim.esm"sv));     // Aura Whisper
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7097C, "Skyrim.esm"sv));     // Marked for Death
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7097D, "Skyrim.esm"sv));     // Storm Call
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7097E, "Skyrim.esm"sv));     // Kyne's Peace
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7097F, "Skyrim.esm"sv));     // Throw Voice
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x70980, "Skyrim.esm"sv));     // Ice Form
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x70981, "Skyrim.esm"sv));     // Subdue
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x30D2, "Dawnguard.esm"sv));   // Summon Durnehviir
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x7CB6, "Dawnguard.esm"sv));   // Soul Tear
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x8A62, "Dawnguard.esm"sv));   // Drain Vitality
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x179D8, "Dragonborn.esm"sv)); // Bend Will
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x1DF92, "Dragonborn.esm"sv)); // Dragon Aspect
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x200C0, "Dragonborn.esm"sv)); // Cyclone
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x2AD09, "Dragonborn.esm"sv)); // Battle Fury

        // Base game - Dragon shouts
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x16CF0, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x252C0, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x4C40B, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x4DBA5, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x549B2, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xDD607, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF80F7, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF80F8, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF80F9, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF80FB, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF8100, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF8101, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF8108, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF8109, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF810A, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xF810B, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xFEA9D, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0xFEAA0, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10C4DF, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10C4E0, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10C4E1, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10C4E2, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10FE21, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x10FE22, "Skyrim.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x18244, "Dawnguard.esm"sv));
        shouts.emplace(handler->LookupForm<RE::TESShout>(0x1A165, "Dawnguard.esm"sv));

        // Stormcrown
        if (handler->LookupLoadedModByName("Stormcrown.esp"sv)) {
            logger::info("Found Stormcrown");
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x14EA7A, "Stormcrown.esp"sv)); // Lightning Breath
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x14EA7F, "Stormcrown.esp"sv)); // Poison Breath
        }

        // Dragon War
        if (handler->LookupLoadedModByName("DragonWar.esp"sv)) {
            logger::info("Found Dragon War");
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x29040, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x29041, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x29042, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x29043, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x9D772, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x9D773, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x9D774, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x9D775, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x334B49, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x334B4F, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x334B52, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x3A4197, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x3A4198, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x3A4199, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x3A419A, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x40E6CC, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x41D9D5, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x41D9DC, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x427BE0, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x42CD2E, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x42CD2F, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x464846, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AA, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AB, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AC, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AD, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AE, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295AF, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295BC, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295BD, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295BE, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295BF, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295C0, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295C1, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295C2, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295C3, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7295C4, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x751E09, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x751E0A, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594A, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594B, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594C, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594D, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594E, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D594F, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5950, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5951, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5952, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5953, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5954, "DragonWar.esp"sv));
            shouts.emplace(handler->LookupForm<RE::TESShout>(0x7D5955, "DragonWar.esp"sv));
        }

        for (const auto& shout : shouts) {
            logger::info("  Cached shout: {}", shout->GetName());
        }
    }
};