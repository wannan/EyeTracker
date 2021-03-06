#ifndef __TOBII_SDK_CORE_ERRORCODES_H__
#define __TOBII_SDK_CORE_ERRORCODES_H__

#define TOBII_SDK_MAKE_ERROR(error)			error

enum {

	//
	// REMEMBER: If you add errors to this file, also add them to
	//			 tobii_sdk_error_convert_code_to_string().
	//

	//
	// REMEMBER: If you add errors to this file, also add them to
	//			 tobii_sdk_error_convert_code_to_string().
	//

	// generic errors
	TOBII_SDK_ERROR_SUCCESS						= TOBII_SDK_MAKE_ERROR(0),
	TOBII_SDK_ERROR_GENERIC						= TOBII_SDK_MAKE_ERROR(1),
	TOBII_SDK_ERROR_INVALID_ARGUMENTS			= TOBII_SDK_MAKE_ERROR(2),
	TOBII_SDK_ERROR_OUT_OF_MEMORY				= TOBII_SDK_MAKE_ERROR(3),
	TOBII_SDK_ERROR_OUT_OF_RANGE				= TOBII_SDK_MAKE_ERROR(4),
	TOBII_SDK_ERROR_NOT_INITIALIZED				= TOBII_SDK_MAKE_ERROR(5),
	TOBII_SDK_ERROR_NOT_SUPPORTED				= TOBII_SDK_MAKE_ERROR(6),
	TOBII_SDK_ERROR_TIMEOUT						= TOBII_SDK_MAKE_ERROR(30),
	TOBII_SDK_ERROR_OPERATION_ABORTED		 	= TOBII_SDK_MAKE_ERROR(31),

	// param stack errors
	TOBII_SDK_ERROR_INVALID_PAYLOAD_ITEM_TYPE	= TOBII_SDK_MAKE_ERROR(7),

	// transport errors
	TOBII_SDK_ERROR_TRANSPORT_ERROR				= TOBII_SDK_MAKE_ERROR(8),
	TOBII_SDK_ERROR_UNKNOWN_OPCODE				= TOBII_SDK_MAKE_ERROR(9),
	TOBII_SDK_ERROR_INVALID_PAYLOAD				= TOBII_SDK_MAKE_ERROR(10),
	TOBII_SDK_ERROR_UNEXPECTED_PAYLOAD			= TOBII_SDK_MAKE_ERROR(11),
	TOBII_SDK_ERROR_EMPTY_PAYLOAD				= TOBII_SDK_MAKE_ERROR(12),

	// factory info
	TOBII_SDK_ERROR_INVALID_FACTORYINFO			= TOBII_SDK_MAKE_ERROR(20),

	// upgrade errors
	TOBII_SDK_ERROR_UPGRADE_GENERIC	            = TOBII_SDK_MAKE_ERROR(40),
	TOBII_SDK_ERROR_UPGRADE_SESSION_MISMATCH	= TOBII_SDK_MAKE_ERROR(41),
	TOBII_SDK_ERROR_UPGRADE_MISSING_PART_ID	  	= TOBII_SDK_MAKE_ERROR(42),
	TOBII_SDK_ERROR_UPGRADE_PACKAGE_VALIDATION	= TOBII_SDK_MAKE_ERROR(43),
	TOBII_SDK_ERROR_UPGRADE_WRONG_MODEL			= TOBII_SDK_MAKE_ERROR(44),
	TOBII_SDK_ERROR_UPGRADE_WRONG_GENERATION	= TOBII_SDK_MAKE_ERROR(45),
	TOBII_SDK_ERROR_UPGRADE_CANT_DOWNGRADE    	= TOBII_SDK_MAKE_ERROR(46),
	TOBII_SDK_ERROR_UPGRADE_DEVICE_DATA_MISSING = TOBII_SDK_MAKE_ERROR(47)

};

#endif // __TOBII_SDK_CORE_ERRORCODES_H__
