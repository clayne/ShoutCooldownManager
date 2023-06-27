#include "Events.h"

#include "Utility.h"

namespace Events {
    OnSpellCastEventHandler* OnSpellCastEventHandler::GetSingleton() {
        static OnSpellCastEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl OnSpellCastEventHandler::ProcessEvent(const RE::TESSpellCastEvent* a_event,
                                                                   RE::BSTEventSource<RE::TESSpellCastEvent>*
                                                                   a_eventSource) {
        if (!a_event) return RE::BSEventNotifyControl::kContinue;

        if (const auto spell = RE::TESForm::LookupByID<RE::SpellItem>(a_event->spell)) {
            if (const auto ref = a_event->object) {
                if (const auto actor = ref->As<RE::Actor>();
                    spell->GetSpellType() == RE::MagicSystem::SpellType::kVoicePower && !actor->IsPlayerRef()) {
                    logger::info("Actor {} used shout {}", actor->GetName(), spell->GetName());
                    if (Utility::actor_shout_cooldown_map.contains(actor)) {
                        auto& shout_cd_map = Utility::actor_shout_cooldown_map.at(actor);
                        std::random_device rd;
                        std::mt19937 rng(rd());
                        std::uniform_int_distribution uni(0, static_cast<int>(shout_cd_map.size()));
                        std::uniform_int_distribution cooldowns(5, 15);
                        if (shout_cd_map.contains(spell->As<RE::TESShout>())) {
                            const auto cd = cooldowns(rng);
                            shout_cd_map.insert_or_assign(spell->As<RE::TESShout>(), std::chrono::system_clock::now() + std::chrono::seconds(cd));
                        }
                        auto random_shout_it = std::next(shout_cd_map.begin(), uni(rng));
                        while (random_shout_it->second != std::chrono::system_clock::time_point::min())
                            random_shout_it = std::next(shout_cd_map.begin(), uni(rng));
                        const auto next_shout = random_shout_it->first;
                        const auto equip_manager = RE::ActorEquipManager::GetSingleton();

                        equip_manager->EquipShout(actor, next_shout);
                        logger::info("Equipped shout {} for actor {}", spell->GetName(), actor->GetName());

                        // Reset cooldowns
                        for (auto& cd : Utility::actor_shout_cooldown_map[actor] | std::views::values) {
                            if ((std::chrono::system_clock::now() - cd).count() <= 0) {
                                logger::info("Shout {} for actor {} has finished cooldown", spell->GetName(), actor->GetName());
                                cd = std::chrono::system_clock::time_point::min();
                            }
                        }
                    }
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }

    void OnSpellCastEventHandler::Register() {
        const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
        holder->AddEventSink(GetSingleton());
        logger::info("Registered spell cast event handler");
    }

    OnObjectLoadedEventHandler* OnObjectLoadedEventHandler::GetSingleton() {
        static OnObjectLoadedEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl OnObjectLoadedEventHandler::ProcessEvent(const RE::TESObjectLoadedEvent* a_event,
                                                                      RE::BSTEventSource<RE::TESObjectLoadedEvent>*
                                                                      a_eventSource) {
        if (!a_event) return RE::BSEventNotifyControl::kContinue;

        if (const auto actor = RE::TESForm::LookupByID<RE::Actor>(a_event->formID)) {
            logger::info("Actor {} loaded", actor->GetName());
            Utility::CacheType shout_to_cd_map;
            for (const auto shout : Utility::shouts) {
                if (actor->HasShout(shout)) {
                    shout_to_cd_map.emplace(shout, std::chrono::system_clock::time_point::min());
                }
            }
            if (!Utility::actor_shout_cooldown_map.contains(actor))
                Utility::actor_shout_cooldown_map.emplace(actor, shout_to_cd_map);
        }

        return RE::BSEventNotifyControl::kContinue;
    }

    void OnObjectLoadedEventHandler::Register() {
        const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
        holder->AddEventSink(GetSingleton());
        logger::info("Registered object loaded event handler");
    }
}
