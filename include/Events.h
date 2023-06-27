#pragma once

namespace Events {
    class OnSpellCastEventHandler : public RE::BSTEventSink<RE::TESSpellCastEvent> {
    protected:
        OnSpellCastEventHandler() = default;

    public:
        OnSpellCastEventHandler(const OnSpellCastEventHandler&) = delete;
        OnSpellCastEventHandler(OnSpellCastEventHandler&&) = delete;
        OnSpellCastEventHandler& operator=(const OnSpellCastEventHandler&) = delete;
        OnSpellCastEventHandler& operator=(OnSpellCastEventHandler&&) = delete;

        static OnSpellCastEventHandler* GetSingleton();
        RE::BSEventNotifyControl ProcessEvent(const RE::TESSpellCastEvent* a_event,
                                              RE::BSTEventSource<RE::TESSpellCastEvent>* a_eventSource) override;
        static void Register();
    };

    class OnObjectLoadedEventHandler : public RE::BSTEventSink<RE::TESObjectLoadedEvent> {
    protected:
        OnObjectLoadedEventHandler() = default;

    public:
        OnObjectLoadedEventHandler(const OnObjectLoadedEventHandler&) = delete;
        OnObjectLoadedEventHandler(OnObjectLoadedEventHandler&&) = delete;
        OnObjectLoadedEventHandler& operator=(const OnObjectLoadedEventHandler&) = delete;
        OnObjectLoadedEventHandler& operator=(OnObjectLoadedEventHandler&&) = delete;

        static OnObjectLoadedEventHandler* GetSingleton();
        RE::BSEventNotifyControl ProcessEvent(const RE::TESObjectLoadedEvent* a_event,
                                              RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource) override;
        static void Register();
    };
}
