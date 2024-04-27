#ifndef ERROR_STATUS_H_
#define ERROR_STATUS_H_


typedef enum {
    E_OK,
    E_NOK,
    E_InputError,
    E_ResourceUnavailable,
    E_Timeout,
    E_InvalidParameter,
	E_ValidParameter,
    E_HardwareFault,
    E_CommunicationError,
    E_OutOfMemory,
    E_UnknownError,
    E_FileNotFound,
    E_FileReadError,
	E_Peripheral_clk_Disabled,
	E_Peripheral_clk_Enabled,
    E_FileWriteError,
    E_NULL_PTR,
    E_NumOfErrors  //to represent the total number of error states
} E_ErrorStatus_t;









#endif  /*ERROR_STATUS_H_*/
