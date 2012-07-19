/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <Rocket/Core/Dictionary.h>
#include <Rocket/Core/ElementText.h>
#include "WidgetTextInputSingleLine.h"

namespace Rocket {
namespace Controls {

WidgetTextInputSingleLine::WidgetTextInputSingleLine(ElementFormControl* parent)
	: WidgetTextInput(parent),
	enter_event_enabled(false)
{
}

WidgetTextInputSingleLine::~WidgetTextInputSingleLine()
{
}

// Sets the value of the text field. The value will be stripped of end-lines.
void WidgetTextInputSingleLine::SetValue(const Core::String& value)
{
	Core::String new_value = value;
	SanitiseValue(new_value);

	WidgetTextInput::SetValue(new_value);
}

void WidgetTextInputSingleLine::SetEnterEventEnabled(bool enabled)
{
	enter_event_enabled = enabled;
}

bool WidgetTextInputSingleLine::IsEnterEventEnabled() const
{
	return enter_event_enabled;
}

// Returns true if the given character is permitted in the input field, false if not.
bool WidgetTextInputSingleLine::IsCharacterValid(Rocket::Core::word character)
{
	return character != '\t' && character != '\n' && character != '\r';
}

// Called when the user pressed enter.
void WidgetTextInputSingleLine::LineBreak()
{
	if (enter_event_enabled)
		DispatchEnterEvent();
	else
		DispatchChangeEvent();
}

// Strips all \n and \r characters from the string.
void WidgetTextInputSingleLine::SanitiseValue(Core::String& value)
{
	Core::String new_value;
	for (Core::String::size_type i = 0; i < value.Length(); ++i)
	{
		switch (value[i])
		{
			case '\n':
			case '\r':
			case '\t':
				break;

			default:
				new_value += value[i];
		}
	}

	value = new_value;
}

}
}
