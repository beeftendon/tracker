#include "stdafx.h"
#include "arduino.h"

using namespace System;

GrblStatus parse_grbl_status(String^ query_response)
{
	GrblStatus grbl_status;
	String^ query_response_edited;

	query_response_edited = query_response->Replace("WPos:", ""); // Remove labels and punctuation in the string to make it easier to split based on delimiter
	query_response_edited = query_response_edited->Replace("<", "");
	query_response_edited = query_response_edited->Replace(">", "");

	String^ delimiter_str= ",";
	array<Char>^ delimiter = delimiter_str->ToCharArray();
	array<String^>^ response_array = query_response_edited->Split(delimiter);

	String^ state = response_array[0];
	if (state->Equals("Idle")) grbl_status.state = GRBL_STATE_IDLE;
	else if (state->Equals("Run")) grbl_status.state = GRBL_STATE_RUN;
	// TODO Implement the other states that probably won't happen

	grbl_status.x = Convert::ToDouble(response_array[1]);
	grbl_status.y = Convert::ToDouble(response_array[2]);
	grbl_status.z = Convert::ToDouble(response_array[3]);

	return grbl_status;
}