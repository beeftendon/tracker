#include <Windows.h>

// Stuff for storing and processing grbl status upon query command ("?")
struct GrblStatus
{
	int state=-1; // See Grbl states for enumerated values
	
	// Positions in working units
	double x;
	double y;
	double z; // Unused but eh, the data is there

public:
	GrblStatus parse_grbl_status(System::String^ query_response);
} ;

// Grbl states
static const int GRBL_STATE_IDLE = 1;
static const int GRBL_STATE_RUN = 2;
//TODO add the rest of the states that probably won't happen

GrblStatus parse_grbl_status(System::String^ query_response);


// Arduino/Grbl initialization
void initialize_grbl(System::IO::Ports::SerialPort arduino_port);