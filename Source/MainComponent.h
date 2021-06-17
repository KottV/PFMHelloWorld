#pragma once

#include <JuceHeader.h>

//struct RepeatingThing;
struct DualButton : juce::Component
{
    DualButton();
    void resized() override;
    void setButton1Handler(std::function<void()> f);
    void setButton2Handler(std::function<void()> f);
private:
    //RepeatingThing& timerThing;
    juce::TextButton button1{ "button1" }, button2{ "button2" };
};

struct MyAsyncHighResGui : juce::Component, juce::AsyncUpdater, juce::HighResolutionTimer
{
    void handleAsyncUpdate() override
    {
        paintColour = (paintColour + 1) % maxColours;
        repaint();
    }
    void hiResTimerCallback() override { triggerAsyncUpdate(); }
    void paint(juce::Graphics& g) override
    {
        switch (paintColour)
        {
        case 0:
            g.setColour(juce::Colours::red);
            break;
        case 1:
            g.setColour(juce::Colours::green);
            break;
        case 2:
            g.setColour(juce::Colours::blue);
            break;
        }
        g.fillAll();
    }

    MyAsyncHighResGui()
    {
        this->startTimer(1000 / 5);

    }
    ~MyAsyncHighResGui()
    {
        stopTimer();
        cancelPendingUpdate();
    }
private:
    int paintColour = 0;
    const int maxColours{ 3 };
};

struct Widget : public juce::Component
{
    Widget(int i) : num(i) {DBG ("widget ctor");}
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::lightgreen);
        g.setColour(juce::Colours::black);
        g.drawRect(getLocalBounds().reduced(2));
        g.drawFittedText(juce::String(num), getLocalBounds(), juce::Justification::centred, 1);
    }

    int num = 0;
};

struct RepeatingThing : juce::Component, juce::Timer
{
    void timerCallback() override
    {
        drawRed = !drawRed;
        repaint();
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(drawRed ? juce::Colours::red : juce::Colours::green);
    }

    RepeatingThing() { startTimerHz(2); }
    ~RepeatingThing() { stopTimer(); }

private:
    bool drawRed = true;


};

struct OwnedArrayComponent : juce::Component, juce::Button::Listener
{
    OwnedArrayComponent();
    ~OwnedArrayComponent();
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
private:
    juce::OwnedArray<juce::TextButton> buttons;
};

struct MyComp : juce::Component
{
    void resized() override {}
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::green); }

    void mouseEnter(const juce::MouseEvent& e) override
    {
//         DBG("mouseEnter");
    }
    void mouseExit(const juce::MouseEvent& e) override
    {
//         DBG("mouseExit");
    }
    
    void mouseMove(const juce::MouseEvent& e) override
    {
//         DBG("mouseMove " << counter);
        ++counter;
    }
private:
        int counter = 0;
};
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

//    void mouseEnter(const juce::MouseEvent& e) override
//    {
////         DBG("MainComponent mouseEnter");
//    }
//    void mouseExit(const juce::MouseEvent& e) override
//    {
////         DBG("MainComponent mouseExit");
//    }
//
//    void mouseMove(const juce::MouseEvent& e) override
//    {
//         DBG("MainComponent mouseMove " << counter);
//        ++counter;
//    }
    void mouseDown(const juce::MouseEvent& e) override
    {
         DBG("clicked ");
    }

private:
    //==============================================================================
    // Your private member variables go here...
//    int counter = 0;
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;
    RepeatingThing repeatingThing;
    DualButton dualButton; // { repeatingThing };
    MyAsyncHighResGui hiResGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
