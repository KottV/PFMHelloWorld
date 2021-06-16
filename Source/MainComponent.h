#pragma once

#include <JuceHeader.h>

struct RepeatingThing;
struct DualButton : juce::Component
{
    DualButton(RepeatingThing&);
    void resized() override;
private:
    RepeatingThing& timerThing;
    juce::TextButton button1{ "button1" }, button2{ "button2" };
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
    DualButton dualButton{ repeatingThing };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
