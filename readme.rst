pycparser version 2.14 can't parse this macro::

    #define MX_ANALOG_MOTOR_STANDARD_FIELDS \
      {-1, -1, "raw_destination", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_destination.analog), \
    	{0}, NULL, 0}, \
      \
      {-1, -1, "raw_position", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_position.analog), \
    	{0}, NULL, (MXFF_IN_DESCRIPTION | MXFF_POLL | MXFF_READ_ONLY)}, \
      \
      {-1, -1, "raw_backlash_correction", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, \
    					raw_backlash_correction.analog), \
    	{0}, NULL, MXFF_IN_DESCRIPTION}, \
      \
      {-1, -1, "raw_negative_limit", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_negative_limit.analog),\
    	{0}, NULL, MXFF_IN_DESCRIPTION}, \
      \
      {-1, -1, "raw_positive_limit", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_positive_limit.analog),\
    	{0}, NULL, MXFF_IN_DESCRIPTION}, \
      \
      {-1, -1, "raw_move_deadband", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_move_deadband.analog),\
    	{0}, NULL, MXFF_IN_DESCRIPTION}, \
      \
      {-1, -1, "raw_set_position", MXFT_DOUBLE, NULL, 0, {0}, \
    	MXF_REC_CLASS_STRUCT, offsetof(MX_MOTOR, raw_set_position.analog), \
    	{0}, NULL, 0}

Specifically, it has trouble with ``offsetof``.

StackOverflow question here:

https://stackoverflow.com/questions/39029209/pycparser-plyparser-parseerror-on-complex-struct

Github issue (mine) here:

https://github.com/eliben/pycparser/issues/143

Older Github issue (not mine) here:

https://github.com/eliben/pycparser/issues/87

Fixed here:

https://github.com/eliben/pycparser/pull/145

https://github.com/eliben/pycparser/commit/de582ad48bd94a15d352e4a43691d26dfd5ff109
