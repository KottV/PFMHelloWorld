#pragma once

#include <JuceHeader.h>

struct MyComp : Component
{
    void resized() override {}
    void paint(Grapgics& g) override { g.fillAlll(Colours::green); }

    void mouseEnter(const MouseEvent& e) override
    {
        DBG("mouseEnter");
    }
    void mouseExit(const MouseEvent& e) override
    {
        DBG("mouseExit");
    }
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

private:
    //==============================================================================
    // Your private member variables go here...

    MyComp comp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
