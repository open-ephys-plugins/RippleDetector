// v060422
#include "RippleDetectorEditor.h"

CustomTextBoxParameterEditor::CustomTextBoxParameterEditor(Parameter* param) : ParameterEditor(param)
{

    jassert(param->getType() == Parameter::FLOAT_PARAM
        || param->getType() == Parameter::INT_PARAM
        || param->getType() == Parameter::STRING_PARAM);

    parameterNameLabel = std::make_unique<Label>("Parameter name", param->getName());
    Font labelFont = Font("Silkscreen", "Regular", 10);
    int labelWidth = 120; //labelFont.getStringWidth(param->getName());
    parameterNameLabel->setFont(labelFont);
    parameterNameLabel->setColour(Label::textColourId, Colours::darkgrey);
    addAndMakeVisible(parameterNameLabel.get());

    if(param->getType() == Parameter::FLOAT_PARAM)
        valueTextBox = std::make_unique<Label>("Parameter value", String(float(param->getValue())));
    else
        valueTextBox = std::make_unique<Label>("Parameter value", param->getValue().toString());

    valueTextBox->setFont(Font("CP Mono", "Plain", 15));
    //valueTextBox->setName(param->getName() + " (" + String(param->getProcessor()->getNodeId()) + ") - " + param->getName());
    valueTextBox->setColour(Label::textColourId, Colours::white);
    valueTextBox->setColour(Label::backgroundColourId, Colours::grey);
    valueTextBox->setEditable(true);
    valueTextBox->addListener(this);
    valueTextBox->setTooltip(param->getDescription());
    addAndMakeVisible(valueTextBox.get());
    
    finalWidth = std::max(labelWidth, 80);

    setBounds(0, 0, labelWidth, 18);
}

void CustomTextBoxParameterEditor::labelTextChanged(Label* label)
{
    if(param->getType() == Parameter::FLOAT_PARAM)
        param->setNextValue(label->getText().getFloatValue());
    else
        param->setNextValue(label->getText());
}

void CustomTextBoxParameterEditor::updateView()
{
    
    if (param != nullptr)
    {
        valueTextBox->setEditable(true);

        if(param->getType() == Parameter::FLOAT_PARAM)
            valueTextBox->setText(String(float(param->getValue())), dontSendNotification);
        else
            valueTextBox->setText(param->getValue().toString(), dontSendNotification);
    }
    else 
	{
        valueTextBox->setEditable(false);
    }

}

void CustomTextBoxParameterEditor::resized()
{
    parameterNameLabel->setBounds(0, 0, int(3 * finalWidth / 5), 18);
    valueTextBox->setBounds(int(3 * finalWidth / 5), 0, int(2 * finalWidth / 5), 18);
}

// Class constructor
RippleDetectorEditor::RippleDetectorEditor(GenericProcessor* parentNode)
	: GenericEditor(parentNode)
{
    
    rippleDetector = (RippleDetector*)parentNode;
    
	desiredWidth = 450; //Plugin's desired width`

    int align1 = 10;

	/* Ripple Detection Settings */
	addSelectedChannelsParameterEditor(Parameter::ParameterScope::STREAM_SCOPE, "Ripple_Input", align1, 25);
    ParameterEditor* rippleInput = getParameterEditor ("Ripple_Input");
    rippleInput->setLayout (ParameterEditor::Layout::nameOnTop);
    rippleInput->setSize (80, 34);

	addComboBoxParameterEditor(Parameter::ParameterScope::STREAM_SCOPE, "Ripple_Out", align1, 60);
    ParameterEditor* rippleOut = getParameterEditor ("Ripple_Out");
    rippleOut->setLayout (ParameterEditor::Layout::nameOnTop);
    rippleOut->setSize (80, 34);

    /* Calibration Button */
	calibrateButton = std::make_unique<UtilityButton>("CALIBRATE");
	calibrateButton->addListener(this);
    calibrateButton->setRadius(3.0f);
    calibrateButton->setBounds(align1, 102, 80, 20);
    addAndMakeVisible(calibrateButton.get());

    /*
	Parameter* param = getProcessor()->getStreamParameter("ripple_std");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 95, 27);

	param = getProcessor()->getStreamParameter("time_thresh");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 95, 52);

	param = getProcessor()->getStreamParameter("refr_time");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 95, 77);

	param = getProcessor()->getStreamParameter("rms_samples");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 95, 102);
    */

    int align2 = 95;

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "ripple_std", align2, 29);
    ParameterEditor* rippleStd = getParameterEditor ("ripple_std");
    rippleStd->setSize (150, 17);

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "time_thresh", align2, 54);
    ParameterEditor* timeThresh = getParameterEditor ("time_thresh");
    timeThresh->setSize (150, 17);

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "refr_time", align2, 79);
    ParameterEditor* refrTime = getParameterEditor ("refr_time");
    refrTime->setSize (150, 17);

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "rms_samples", align2, 104);
    ParameterEditor* rmsSamples = getParameterEditor ("rms_samples");
    rmsSamples->setSize (150, 17);

	/* EMG / ACC Movement Detection Settings */
    int align3 = 250;
	addComboBoxParameterEditor(Parameter::ParameterScope::STREAM_SCOPE, "mov_detect", align3, 22);
    ParameterEditor* movDetect = getParameterEditor ("mov_detect");
    movDetect->setLayout (ParameterEditor::Layout::nameOnTop);
    movDetect->setSize (90, 34);

	addSelectedChannelsParameterEditor(Parameter::ParameterScope::STREAM_SCOPE, "Mov_Input", align3, 57);
    ParameterEditor* movInput = getParameterEditor ("Mov_Input");
    movInput->setLayout (ParameterEditor::Layout::nameOnTop);
    movInput->setSize (90, 34);

	addComboBoxParameterEditor(Parameter::ParameterScope::STREAM_SCOPE, "Mov_Out", align3, 92);
    ParameterEditor* movOut = getParameterEditor ("Mov_Out");
    movOut->setLayout (ParameterEditor::Layout::nameOnTop);
    movOut->setSize (90, 34);

    /*
	param = getProcessor()->getStreamParameter("mov_std");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 325, 25);

	param = getProcessor()->getStreamParameter("min_time_st");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 325, 50);

	param = getProcessor()->getStreamParameter("min_time_mov");
    addCustomParameterEditor(new CustomTextBoxParameterEditor(param), 325, 75);
    */

    int align4 = 345;
    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "mov_std", align4, 22);
    ParameterEditor* movStd = getParameterEditor ("mov_std");
    movStd->setLayout (ParameterEditor::Layout::nameOnTop);
    movStd->setSize (90, 34);

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "min_time_st", align4, 57);
    ParameterEditor* minTimeSt = getParameterEditor ("min_time_st");
    minTimeSt->setLayout (ParameterEditor::Layout::nameOnTop);
    minTimeSt->setSize (90, 34);

    addTextBoxParameterEditor(Parameter::STREAM_SCOPE, "min_time_mov", align4, 92);
    ParameterEditor* minTimeMov = getParameterEditor ("min_time_mov");
    minTimeMov->setLayout (ParameterEditor::Layout::nameOnTop);
    minTimeMov->setSize (90, 34);
}

void RippleDetectorEditor::buttonClicked(Button*)
{
	/* Calibration button was clicked */
	rippleDetector->shouldCalibrate = true;
}

// Called when settings are updated
void RippleDetectorEditor::updateSettings() {}
