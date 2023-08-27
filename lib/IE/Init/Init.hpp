#pragma once

#include <filesystem>

#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Sprite/Sprite.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/RoundedRectangle/RoundedRectangle.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Video/videoConvert.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Video/VideoFromFile/VideoFromFile.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/Caption/Caption.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/Bar/Bar.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxBorderHorizontal/BoxBorderHorizontal.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxBorderVertical/BoxBorderVertical.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxBorder/BoxBorder.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxConstRatio/BoxConstRatio.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxConstBezel/BoxConstBezel.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxConstRatioCenter/BoxConstRatioCenter.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxConstBorder/BoxConstBorder.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxPanel/BoxPanel.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxAlternative/BoxAlternative.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxMovableBorder/BoxMovableBorder.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxBackground//BoxBackground.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxShader/BoxShader.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxUninteractive/BoxUninteractive.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxMakePermeable/BoxMakePermeable.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxScroll/BoxScroll.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxSwitch/BoxSwitch.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxTabs/BoxTabs.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxSwitcherTabs/BoxSwitcherTabs.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxConstCenter/BoxConstCenter.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BaseSlider/ConstSlider/ConstSlider.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BaseSlider/Slider/Slider.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BasicBaseButton/Button/Button.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BasicBaseButton/ButtonPanel/ButtonPanel.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/Switcher/Switcher.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/Text.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/BaseTextBlock/InteractiveTextBlock/InteractiveTextBlock.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/BaseTextBlock/ObjectTextBlock/ObjectTextBlock.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/BaseLine/Underline/Underline.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/BaseLine/StrikeThrough/StrikeThrough.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextHotkeyInteraction/TextHotkeyInteraction.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Interface/Interface.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxSwitchTabs/BaseSwitchTabsAction/SwitchTabsAction/SwitchTabsAction.hpp"
#include "IE/IComponent/IUnscalable/IScalable/Box/BoxSwitchTabs/BaseSwitchTabsAction/WhileSwitchTabsAction/WhileSwitchTabsAction.hpp"
#include "IE/SizingAndPositioning/ISizing/ConstSizing/ConstSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/RelativeNormalSizing/RelativeNormalSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/RelativeParentSizing/RelativeParentSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/ParentCoefficientSizing/ParentCoefficientSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/TargetCoefficientSizing/TargetCoefficientSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/SmartSizing/SmartSizing.hpp"
#include "IE/SizingAndPositioning/ISizing/LambdaSizing/LambdaSizing.hpp"
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicMouseLambdaInteraction/BasicMouseLambdaInteraction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicOpenUrlAction/BasicOpenUrlAction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicCloseWindowAction/BasicCloseWindowAction.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/Switcher/SwitherAction/SwitcherAction.hpp"
#include "../Modules/yaml-cpp/shared/value/KeyAction/SetSValueAction/SetSValueAction.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/toBool/equals/sConvertToBoolEquals.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/toBool/greater/sConvertToBoolGreater.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/toBool/less/sConvertToBoolLess.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/toBool/lessOrEquals/sConvertToBoolLessOrEquals.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/toBool/greaterOrEquals/sConvertToBoolGreaterOrEquals.hpp"
#include "../Modules/yaml-cpp/shared/value/converts/range/general/sConvertRange.hpp"
#include "IE/Animation/Animator/IAnimatorUnit/Animation/Animation.hpp"
#include "IE/Animation/Animator/IAnimatorUnit/Prerequisite/Prerequisite.hpp"
#include "IE/Animation/Animator/IAnimatorUnit/AnimatorUnitMatch/AnimatorUnitMatch.hpp"
#include "IE/Animation/IChangeVariable/ChangeVariableByStraightLine/ChangeVariableByStraightLine.hpp"
#include "IE/Animation/IChangeVariable/ChangeVariableByBrokenLine/ChangeVariableByBrokenLine.hpp"
#include "IE/Animation/IChangeVariable/ChangeVariableBySteppedLine/ChangeVariableBySteppedLine.hpp"
#include "IE/Animation/IChangeVariable/ChangeVariableBySinusoid/ChangeVariableBySinusoid.hpp"
#include "IE/Animation/IChangeVariable/ChangeVariableByCurve//ChangeVariableByCurve.hpp"
#include "IE/Debug/BoxDebug.hpp"

namespace ie {
	void init(int argc = 0, char *argv[] = {}, std::filesystem::path modulesList = {});
	
	void yamlBuilderInit();
}