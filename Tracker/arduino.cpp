#include "stdafx.h"
#include "arduino.h"

using namespace System;

GrblStatus parse_grbl_status(String^ query_response)
{
	GrblStatus grbl_status;

	query_response->Replace("WPos:", ""); // Remove labels in the string to make it easier to split based on delimiter
	String^ delimiter_str= ",";
	array<Char>^ delimiter = delimiter_str->ToCharArray();
	array<String^>^ response_array = query_response->Split(delimiter);

	String^ state = response_array[0];
	if (state->Equals("Idle")) grbl_status.state = GRBL_STATE_IDLE;
	else if (state->Equals("Run")) grbl_status.state = GRBL_STATE_RUN;
	// TODO Implement the other states that probably won't happen

	grbl_status.x = Convert::ToInt32(response_array[1]);
	grbl_status.y = Convert::ToInt32(response_array[2]);
	grbl_status.z = Convert::ToInt32(response_array[3]);

	return grbl_status;
}