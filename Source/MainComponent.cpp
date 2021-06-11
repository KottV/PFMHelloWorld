#include "MainComponent.h"



OwnedArrayComponent::OwnedArrayComponent()
{
    for (int i; i < 10; ++i)
    {
        auto* widget = buttons.add(new juce::TextButton(juce::String(i)));
        addAndMakeVisible(widget);
        widget->addListener(this);
    }
}

OwnedArrayComponent::~OwnedArrayComponent()
{
    for (auto* widget : buttons)
    {
        widget->removeListener(this);
    }
}    

void OwnedArrayComponent::resized()
{
    auto width = getWidth() / static_cast<float>(buttons.size());
    int x = 0;
    auto h = getHeight();
    
    for (auto* widget : buttons)
    {
        widget->setBounds(x, 0, width, h);
        x += width;
    }
}

void::OwnedArrayComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == buttons.getFirst())
    {
        DBG("First Button");
    }
    
    else if (buttonThatWasClicked == buttons.getLast())
    {
        DBG("Last Button");
    }
    
    else
    {
        DBG("Other Button");
    }
}
//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(ownedArrayComp);
    addAndMakeVisible(comp);
    setSize (600, 400);
    comp.addMouseListener(this, false);
}

MainComponent::~MainComponent()
{
    comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (32.0f));
    g.setColour (juce::Colours::white);
     g.drawText ("Hello World!", getLocalBounds(), juce::Justification::top, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    comp.setBounds(30, 30, 100, 100);
    ownedArrayComp.setBounds(comp.getX(),
                             comp.getBottom() + 5, 
                             getWidth() - 60, 
                             getHeight() - comp.getHeight() - 60);
}
