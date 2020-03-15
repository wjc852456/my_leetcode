#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 468 找到字符串中所有字母异位词

#define VALIDCHAR(c) \
        ((c >= '0' && c <= '9') || \
         (c >= 'a' && c <= 'f') || \
         (c >= 'A' && c <= 'F') || \
         (c == '.') || \
         (c == ':'))

int ValidIPV4(char* ipValue, int ipid)
{
    if (ipid > 3 || ipid == 0) {
        return -1;
    }
    int value = 0;
    for (int i = 0; i < ipid; ++i) {
        if (i == 0 && ipValue[0] == '0' && ipid > 1) {
            return -1;
        }
        int num = (ipValue[i] - '0');
        double pre = pow(10, ipid - i - 1);
        value += num * (int)pre;
    }
    if (value >= 0 && value <= 255) {
        return 0;
    } else {
        return -1;
    }
}

int ValidIPV6(char* ipValue, int ipid)
{
    if (ipid > 4 || ipid == 0) {
        return -1;
    }
    for (int i = 0; i < ipid; ++i) {
        if (VALIDCHAR(ipValue[i])) {
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
}

char * validIPAddress(char * IP)
{
    char ipValue[4];
    int ipid = 0;
    int validFlag;
    int ipV4Flag = 0;
    int ipV6Flag = 0;
    int ipV4_num = 0;
    int ipV6_num = 0;
    while (*IP) {
        char curchar = *IP;
        if (VALIDCHAR(curchar)) {
            if (curchar == '.') {
                ipV4_num++;
                if (ipV4_num > 3) {
                    return "Neither";
                }
                ipV4Flag = 1;
                if (ipV6Flag) {
                    return "Neither";
                }
                validFlag = ValidIPV4(ipValue, ipid);
                if (validFlag != 0) {
                    return "Neither";
                }
                ipid = 0;
            } else if (curchar == ':') {
                ipV6_num++;
                if (ipV6_num > 7) {
                    return "Neither";
                }
                ipV6Flag = 1;
                if (ipV4Flag) {
                    return "Neither";
                }
                validFlag = ValidIPV6(ipValue, ipid);
                if (validFlag != 0) {
                    return "Neither";
                }
                ipid = 0;
            } else {
                if (ipid >= 4) {
                    return "Neither";
                }
                ipValue[ipid] = *IP;
                ipid++;
            }
        } else {
            return "Neither";
        }
        IP++;
    }

    if (ipV4Flag && !ipV6Flag) {
        if (ipV4_num != 3) {
            return "Neither";
        }
        validFlag = ValidIPV4(ipValue, ipid);
        if (validFlag != 0) {
            return "Neither";
        } else {
            return "IPv4";
        }
    } else if (ipV6Flag && !ipV4Flag) {
        if (ipV6_num != 7) {
            return "Neither";
        }
        validFlag = ValidIPV6(ipValue, ipid);
        if (validFlag != 0) {
            return "Neither";
        } else {
            return "IPv6";
        }
    } else {
        return "Neither";
    }
}


int main(int argc, char *argv[])
{
    //char IP[] = "172.16.254.1";
    //char IP[] = "2001:0db8:85a3:0:0:8A2E:0370:7334";
    //char IP[] = "2001:0db8:85a3:00000:0:8A2E:0370:7334";
    char IP[] = "192.0.0.1";
    char* res = validIPAddress(IP);
    printf("%s\n", res);
    return 0;
}