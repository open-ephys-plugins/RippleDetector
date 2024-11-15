// v060422
#ifndef __RIPPLE_DETECTOR_EDITOR_H
#define __RIPPLE_DETECTOR_EDITOR_H

#include <EditorHeaders.h> 
#include <sstream>
#include <iomanip>

#include "RippleDetector.h"

class RippleDetectorEditor : public GenericEditor,
                        public Button::Listener
{
public:
    RippleDetectorEditor(GenericProcessor* parentNode);
    virtual ~RippleDetectorEditor() {}

    void buttonClicked(Button*);
    void updateSettings() override;

private:
    
    RippleDetector* rippleDetector;

    std::unique_ptr<UtilityButton> calibrateButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RippleDetectorEditor);
};
#endif