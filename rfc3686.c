
#include <stdio.h>
#include <string.h>
#include "aes.h"

typedef struct 
{   unsigned int  k_len;
    unsigned int  m_len;
    unsigned char key[32];
    unsigned char iv[8];
    unsigned char nonce[8];
    unsigned char p_txt[36];
    unsigned char c_str[48];
    unsigned char k_str[48];
    unsigned char c_txt[36];
} test_str;

test_str tests[] = 
{
 {  16, 16, /* Vector 1 */
  { 0xae, 0x68, 0x52, 0xf8, 0x12, 0x10, 0x67, 0xcc, 
    0x4b, 0xf7, 0xa5, 0x76, 0x55, 0x77, 0xf3, 0x9e 
  },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  { 0x00, 0x00, 0x00, 0x30
  },
  /* "Single block msg" */
  { 0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x62, 
    0x6c, 0x6f, 0x63, 0x6b, 0x20, 0x6d, 0x73, 0x67 
  },
  { 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
  }, 
  { 0xb7, 0x60, 0x33, 0x28, 0xdb, 0xc2, 0x93, 0x1b, 
    0x41, 0x0e, 0x16, 0xc8, 0x06, 0x7e, 0x62, 0xdf
  },
  { 0xe4, 0x09, 0x5d, 0x4f, 0xb7, 0xa7, 0xb3, 0x79, 
    0x2d, 0x61, 0x75, 0xa3, 0x26, 0x13, 0x11, 0xb8 
  }
 },
 {  16, 32, /* Vector 2 */
  { 0x7e, 0x24, 0x06, 0x78, 0x17, 0xfa, 0xe0, 0xd7, 
    0x43, 0xd6, 0xce, 0x1f, 0x32, 0x53, 0x91, 0x63
  },
  { 0xc0, 0x54, 0x3b, 0x59, 0xda, 0x48, 0xd9, 0x0b 
  }, 
  { 0x00, 0x6c, 0xb6, 0xdb
  },
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  },
  { 0x00, 0x6c, 0xb6, 0xdb, 0xc0, 0x54, 0x3b, 0x59, 
    0xda, 0x48, 0xd9, 0x0b, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x6c, 0xb6, 0xdb, 0xc0, 0x54, 0x3b, 0x59, 
    0xda, 0x48, 0xd9, 0x0b, 0x00, 0x00, 0x00, 0x02
  }, 
  { 0x51, 0x05, 0xa3, 0x05, 0x12, 0x8f, 0x74, 0xde, 
    0x71, 0x04, 0x4b, 0xe5, 0x82, 0xd7, 0xdd, 0x87, 
    0xfb, 0x3f, 0x0c, 0xef, 0x52, 0xcf, 0x41, 0xdf, 
    0xe4, 0xff, 0x2a, 0xc4, 0x8d, 0x5c, 0xa0, 0x37
  },
  { 0x51, 0x04, 0xa1, 0x06, 0x16, 0x8a, 0x72, 0xd9, 
    0x79, 0x0d, 0x41, 0xee, 0x8e, 0xda, 0xd3, 0x88,
    0xeb, 0x2e, 0x1e, 0xfc, 0x46, 0xda, 0x57, 0xc8, 
    0xfc, 0xe6, 0x30, 0xdf, 0x91, 0x41, 0xbe, 0x28 
  }
 },
 {  16, 36, /* Vector 3 */
  { 0x76, 0x91, 0xbe, 0x03, 0x5e, 0x50, 0x20, 0xa8, 
    0xac, 0x6e, 0x61, 0x85, 0x29, 0xf9, 0xa0, 0xdc 
  },
  { 0x27, 0x77, 0x7f, 0x3f,  0x4a, 0x17, 0x86, 0xf0 
  },
  { 0x00, 0xe0, 0x01, 0x7b
  }, 
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
    0x20, 0x21, 0x22, 0x23
  }, 
  { 0x00, 0xe0, 0x01, 0x7b, 0x27, 0x77, 0x7f, 0x3f, 
    0x4a, 0x17, 0x86, 0xf0, 0x00, 0x00, 0x00, 0x01,
    0x00, 0xe0, 0x01, 0x7b, 0x27, 0x77, 0x7f, 0x3f, 
    0x4a, 0x17, 0x86, 0xf0, 0x00, 0x00, 0x00, 0x02, 
    0x00, 0xe0, 0x01, 0x7b, 0x27, 0x77, 0x7f, 0x3f, 
    0x4a, 0x17, 0x86, 0xf0, 0x00, 0x00, 0x00, 0x03 
  },
  { 0xc1, 0xce, 0x4a, 0xab, 0x9b, 0x2a, 0xfb, 0xde, 
    0xc7, 0x4f, 0x58, 0xe2, 0xe3, 0xd6, 0x7c, 0xd8, 
    0x55, 0x51, 0xb6, 0x38, 0xca, 0x78, 0x6e, 0x21, 
    0xcd, 0x83, 0x46, 0xf1, 0xb2, 0xee, 0x0e, 0x4c, 
    0x05, 0x93, 0x25, 0x0c, 0x17, 0x55, 0x36, 0x00, 
    0xa6, 0x3d, 0xfe, 0xcf, 0x56, 0x23, 0x87, 0xe9
  }, 
  { 0xc1, 0xcf, 0x48, 0xa8, 0x9f, 0x2f, 0xfd, 0xd9, 
    0xcf, 0x46, 0x52, 0xe9, 0xef, 0xdb, 0x72, 0xd7, 
    0x45, 0x40, 0xa4, 0x2b, 0xde, 0x6d, 0x78, 0x36, 
    0xd5, 0x9a, 0x5c, 0xea, 0xae, 0xf3, 0x10, 0x53, 
    0x25, 0xb2, 0x07, 0x2f 
  }
 },
 {  24, 16, /* Vector 4 */
  { 0x16, 0xaf, 0x5b, 0x14, 0x5f, 0xc9, 0xf5, 0x79, 
    0xc1, 0x75, 0xf9, 0x3e, 0x3b, 0xfb, 0x0e, 0xed, 
    0x86, 0x3d, 0x06, 0xcc, 0xfd, 0xb7, 0x85, 0x15 
  },
  { 0x36, 0x73, 0x3c, 0x14, 0x7d, 0x6d, 0x93, 0xcb
  },
  { 0x00, 0x00, 0x00, 0x48
  }, 
  /* "Single block msg" */
  { 0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x62, 
    0x6c, 0x6f, 0x63, 0x6b, 0x20, 0x6d, 0x73, 0x67 
  },
  { 0x00, 0x00, 0x00, 0x48, 0x36, 0x73, 0x3c, 0x14, 
    0x7d, 0x6d, 0x93, 0xcb, 0x00, 0x00, 0x00, 0x01 
  },
  { 0x18, 0x3c, 0x56, 0x28, 0x8e, 0x3c, 0xe9, 0xaa, 
    0x22, 0x16, 0x56, 0xcb, 0x23, 0xa6, 0x9a, 0x4f
  },
  { 0x4b, 0x55, 0x38, 0x4f, 0xe2, 0x59, 0xc9, 0xc8, 
    0x4e, 0x79, 0x35, 0xa0, 0x03, 0xcb, 0xe9, 0x28
  }
 },
 {  24, 32, /* Vector 5 */
  { 0x7c, 0x5c, 0xb2, 0x40, 0x1b, 0x3d, 0xc3, 0x3c, 
    0x19, 0xe7, 0x34, 0x08, 0x19, 0xe0, 0xf6, 0x9c, 
    0x67, 0x8c, 0x3d, 0xb8, 0xe6, 0xf6, 0xa9, 0x1a 
  },
  { 0x02, 0x0c, 0x6e, 0xad, 0xc2, 0xcb, 0x50, 0x0d
  },  
  { 0x00, 0x96, 0xb0, 0x3b 
  },
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
  },
  { 0x00, 0x96, 0xb0, 0x3b, 0x02, 0x0c, 0x6e, 0xad, 
    0xc2, 0xcb, 0x50, 0x0d, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0x96, 0xb0, 0x3b, 0x02, 0x0c, 0x6e, 0xad, 
    0xc2, 0xcb, 0x50, 0x0d, 0x00, 0x00, 0x00, 0x02 
  },
  { 0x45, 0x33, 0x41, 0xff, 0x64, 0x9e, 0x25, 0x35, 
    0x76, 0xd6, 0xa0, 0xf1, 0x7d, 0x3c, 0xc3, 0x90,
    0x94, 0x81, 0x62, 0x0f, 0x4e, 0xc1, 0xb1, 0x8b, 
    0xe4, 0x06, 0xfa, 0xe4, 0x5e, 0xe9, 0xe5, 0x1f
  },
  { 0x45, 0x32, 0x43, 0xfc, 0x60, 0x9b, 0x23, 0x32, 
    0x7e, 0xdf, 0xaa, 0xfa, 0x71, 0x31, 0xcd, 0x9f, 
    0x84, 0x90, 0x70, 0x1c, 0x5a, 0xd4, 0xa7, 0x9c, 
    0xfc, 0x1f, 0xe0, 0xff, 0x42, 0xf4, 0xfb, 0x00 
  }
 },
 {  24, 36, /* Vector 6 */
  { 0x02, 0xbf, 0x39, 0x1e, 0xe8, 0xec, 0xb1, 0x59, 
    0xb9, 0x59, 0x61, 0x7b, 0x09, 0x65, 0x27, 0x9b, 
    0xf5, 0x9b, 0x60, 0xa7, 0x86, 0xd3, 0xe0, 0xfe
  }, 
  { 0x5c, 0xbd, 0x60, 0x27, 0x8d, 0xcc, 0x09, 0x12
  }, 
  { 0x00, 0x07, 0xbd, 0xfd
  }, 
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23 
  },
  { 0x00, 0x07, 0xbd, 0xfd, 0x5c, 0xbd, 0x60, 0x27, 
    0x8d, 0xcc, 0x09, 0x12, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0x07, 0xbd, 0xfd, 0x5c, 0xbd, 0x60, 0x27, 
    0x8d, 0xcc, 0x09, 0x12, 0x00, 0x00, 0x00, 0x03, 
    0x00, 0x07, 0xbd, 0xfd, 0x5c, 0xbd, 0x60, 0x27, 
    0x8d, 0xcc, 0x09, 0x12, 0x00, 0x00, 0x00, 0x02
  }, 
  { 0x96, 0x88, 0x3d, 0xc6, 0x5a, 0x59, 0x74, 0x28, 
    0x5c, 0x02, 0x77, 0xda, 0xd1, 0xfa, 0xe9, 0x57, 
    0xc2, 0x99, 0xae, 0x86, 0xd2, 0x84, 0x73, 0x9f, 
    0x5d, 0x2f, 0xd2, 0x0a, 0x7a, 0x32, 0x3f, 0x97, 
    0x8b, 0xcf, 0x2b, 0x16, 0x39, 0x99, 0xb2, 0x26, 
    0x15, 0xb4, 0x9c, 0xd4, 0xfe, 0x57, 0x39, 0x98 
  },
  { 0x96, 0x89, 0x3f, 0xc5, 0x5e, 0x5c, 0x72, 0x2f, 
    0x54, 0x0b, 0x7d, 0xd1, 0xdd, 0xf7, 0xe7, 0x58, 
    0xd2, 0x88, 0xbc, 0x95, 0xc6, 0x91, 0x65, 0x88, 
    0x45, 0x36, 0xc8, 0x11, 0x66, 0x2f, 0x21, 0x88, 
    0xab, 0xee, 0x09, 0x35 
  }
 },
 {  32, 16, /* Vector 7 */
  { 0x77, 0x6b, 0xef, 0xf2, 0x85, 0x1d, 0xb0, 0x6f, 
    0x4c, 0x8a, 0x05, 0x42, 0xc8, 0x69, 0x6f, 0x6c, 
    0x6a, 0x81, 0xaf, 0x1e, 0xec, 0x96, 0xb4, 0xd3, 
    0x7f, 0xc1, 0xd6, 0x89, 0xe6, 0xc1, 0xc1, 0x04
  },
  { 0xdb, 0x56, 0x72, 0xc9, 0x7a, 0xa8, 0xf0, 0xb2 
  }, 
  { 0x00, 0x00, 0x00, 0x60
  }, 
  /* "Single block msg" */
  { 0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x62, 
    0x6c, 0x6f, 0x63, 0x6b, 0x20, 0x6d, 0x73, 0x67
  },
  { 0x00, 0x00, 0x00, 0x60, 0xdb, 0x56, 0x72, 0xc9, 
    0x7a, 0xa8, 0xf0, 0xb2, 0x00, 0x00, 0x00, 0x01
  },
  { 0x47, 0x33, 0xbe, 0x7a, 0xd3, 0xe7, 0x6e, 0xa5, 
    0x3a, 0x67, 0x00, 0xb7, 0x51, 0x8e, 0x93, 0xa7
  }, 
  { 0x14, 0x5a, 0xd0, 0x1d, 0xbf, 0x82, 0x4e, 0xc7, 
    0x56, 0x08, 0x63, 0xdc, 0x71, 0xe3, 0xe0, 0xc0 
  }
 },
 {  32, 32, /* Vector 8 */
  { 0xf6, 0xd6, 0x6d, 0x6b, 0xd5, 0x2d, 0x59, 0xbb, 
    0x07, 0x96, 0x36, 0x58, 0x79, 0xef, 0xf8, 0x86, 
    0xc6, 0x6d, 0xd5, 0x1a, 0x5b, 0x6a, 0x99, 0x74, 
    0x4b, 0x50, 0x59, 0x0c, 0x87, 0xa2, 0x38, 0x84 
  },
  { 0xc1, 0x58, 0x5e, 0xf1, 0x5a, 0x43, 0xd8, 0x75
  }, 
  { 0x00, 0xfa, 0xac, 0x24
  },
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f 
  },
  { 0x00, 0xfa, 0xac, 0x24, 0xc1, 0x58, 0x5e, 0xf1, 
    0x5a, 0x43, 0xd8, 0x75, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0xfa, 0xac, 0x24, 0xc1, 0x58, 0x5e, 0xf1, 
    0x5a, 0x43, 0xd8, 0x75, 0x00, 0x00, 0x00, 0x02 
  },
  { 0xf0, 0x5f, 0x21, 0x18, 0x3c, 0x91, 0x67, 0x2b, 
    0x41, 0xe7, 0x0a, 0x00, 0x8c, 0x43, 0xbc, 0xa6, 
    0xa8, 0x21, 0x79, 0x43, 0x9b, 0x96, 0x8b, 0x7d, 
    0x4d, 0x29, 0x99, 0x06, 0x8f, 0x59, 0xb1, 0x03 
  },
  { 0xf0, 0x5e, 0x23, 0x1b, 0x38, 0x94, 0x61, 0x2c, 
    0x49, 0xee, 0x00, 0x0b, 0x80, 0x4e, 0xb2, 0xa9, 
    0xb8, 0x30, 0x6b, 0x50, 0x8f, 0x83, 0x9d, 0x6a, 
    0x55, 0x30, 0x83, 0x1d, 0x93, 0x44, 0xaf, 0x1c 
  }
 },
 {  32, 36, /* Vector 9 */
  { 0xff, 0x7a, 0x61, 0x7c, 0xe6, 0x91, 0x48, 0xe4, 
    0xf1, 0x72, 0x6e, 0x2f, 0x43, 0x58, 0x1d, 0xe2, 
    0xaa, 0x62, 0xd9, 0xf8, 0x05, 0x53, 0x2e, 0xdf, 
    0xf1, 0xee, 0xd6, 0x87, 0xfb, 0x54, 0x15, 0x3d
  },
  { 0x51, 0xa5, 0x1d, 0x70, 0xa1, 0xc1, 0x11, 0x48
  },
  { 0x00, 0x1c, 0xc5, 0xb7
  },
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
    0x20, 0x21, 0x22, 0x23 
  },
  { 0x00, 0x1c, 0xc5, 0xb7, 0x51, 0xa5, 0x1d, 0x70, 
    0xa1, 0xc1, 0x11, 0x48, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0x1c, 0xc5, 0xb7, 0x51, 0xa5, 0x1d, 0x70, 
    0xa1, 0xc1, 0x11, 0x48, 0x00, 0x00, 0x00, 0x02, 
    0x00, 0x1c, 0xc5, 0xb7, 0x51, 0xa5, 0x1d, 0x70, 
    0xa1, 0xc1, 0x11, 0x48, 0x00, 0x00, 0x00, 0x03 
  },
  { 0xeb, 0x6d, 0x50, 0x81, 0x19, 0x0e, 0xbd, 0xf0, 
    0xc6, 0x7c, 0x9e, 0x4d, 0x26, 0xc7, 0x41, 0xa5, 
    0xa4, 0x16, 0xcd, 0x95, 0x71, 0x7c, 0xeb, 0x10, 
    0xec, 0x95, 0xda, 0xae, 0x9f, 0xcb, 0x19, 0x00, 
    0x3e, 0xe1, 0xc4, 0x9b, 0xc6, 0xb9, 0xca, 0x21, 
    0x3f, 0x6e, 0xe2, 0x71, 0xd0, 0xa9, 0x33, 0x39
  }, 
  { 0xeb, 0x6c, 0x52, 0x82, 0x1d, 0x0b, 0xbb, 0xf7, 
    0xce, 0x75, 0x94, 0x46, 0x2a, 0xca, 0x4f, 0xaa, 
    0xb4, 0x07, 0xdf, 0x86, 0x65, 0x69, 0xfd, 0x07, 
    0xf4, 0x8c, 0xc0, 0xb5, 0x83, 0xd6, 0x07, 0x1f, 
    0x1e, 0xc0, 0xe6, 0xb8 
  }
 }
};

void rfc3686_inc(unsigned char ctr_buf[AES_BLOCK_SIZE])
{
    if(!(++(ctr_buf[15])))
        if(!(++(ctr_buf[14])))
            if(!(++(ctr_buf[13])))
                ++(ctr_buf[12]);
}

void rfc3686_init( unsigned char nonce[4], unsigned char iv[8], unsigned char ctr_buf[AES_BLOCK_SIZE])
{
    memcpy(ctr_buf, nonce, 4);
    memcpy(ctr_buf +  4, iv, 8);
    memset(ctr_buf + 12, 0, 4); 
    rfc3686_inc(ctr_buf);
}

AES_RETURN rfc3686_crypt(const unsigned char *ibuf, unsigned char *obuf, int len, 
                                                unsigned char *cbuf, aes_encrypt_ctx cx[1])
{
    return aes_ctr_crypt(ibuf, obuf, len, cbuf, rfc3686_inc, cx);
}

void rfc3686_test(void)
{   aes_encrypt_ctx aes_ctx[1];
    unsigned char ctr_buf[AES_BLOCK_SIZE];
    unsigned char obuf[36];
    unsigned int i; 
    
    for( i = 0 ; i < sizeof(tests) / sizeof(test_str) ; ++i )
    {
        aes_encrypt_key(tests[i].key, tests[i].k_len, aes_ctx);
        rfc3686_init(tests[i].nonce, tests[i].iv, ctr_buf);
        rfc3686_crypt(tests[i].p_txt, obuf, tests[i].m_len, ctr_buf, aes_ctx);
        if(memcmp(obuf, tests[i].c_txt, tests[i].m_len) != 0)
            printf("\nerror");
    }
}

int main(void)
{
    rfc3686_test();
    return 0;
}
