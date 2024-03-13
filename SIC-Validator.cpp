#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<string> VALID_ONE_BYTE_OPCODES = {"C4", "C0", "F4", "C8", "F0", "F8"};
vector<string> VALID_TWO_BYTE_OPCODES = {
    "90",
    "B4",
    "A0",
    "9C",
    "98",
    "AC",
    "A4",
    "A8",
    "94",
    "B0",
    "B8",
};
vector<string> VALID_THREE_OR_FOUR_BYTE_OPCODES = {
    "18",
    "58",
    "40",
    "28",
    "88",
    "24",
    "64",
    "3C",
    "30",
    "34",
    "38",
    "48",
    "00",
    "68",
    "50",
    "70",
    "08",
    "6C",
    "74",
    "04",
    "D0",
    "20",
    "60",
    "44",
    "D8",
    "4C",
    "EC",
    "0C",
    "78",
    "54",
    "80",
    "D4",
    "14",
    "7C",
    "E8",
    "84",
    "10",
    "1C",
    "5C",
    "E0",
    "2C",
    "DC",
};

vector<int> VALID_REGISTERS = {0, 1, 2, 3, 4, 5, 6, 8, 9};

string convertHexToBin(string hex)
{
  string bin = "";
  for (int i = 0; i < hex.length(); i++)
  {
    switch (hex[i])
    {
    case '0':
      bin += "0000";
      break;
    case '1':
      bin += "0001";
      break;
    case '2':
      bin += "0010";
      break;
    case '3':
      bin += "0011";
      break;
    case '4':
      bin += "0100";
      break;
    case '5':
      bin += "0101";
      break;
    case '6':
      bin += "0110";
      break;
    case '7':
      bin += "0111";
      break;
    case '8':
      bin += "1000";
      break;
    case '9':
      bin += "1001";
      break;
    case 'A':
    case 'a':
      bin += "1010";
      break;
    case 'B':
    case 'b':
      bin += "1011";
      break;
    case 'C':
    case 'c':
      bin += "1100";
      break;
    case 'D':
    case 'd':
      bin += "1101";
      break;
    case 'E':
    case 'e':
      bin += "1110";
      break;
    case 'F':
    case 'f':
      bin += "1111";
      break;
    default:
      cout << "Invalid hexadecimal digit " << hex[i] << endl;
    }
  }
  return bin;
}

string checkOneByteHexcode(string hexcode)
{
  for (int i = 0; i < VALID_ONE_BYTE_OPCODES.size(); i++)
  {
    if (hexcode == VALID_ONE_BYTE_OPCODES[i])
    {
      return "Valid 1 byte hexcode";
    }
  }
  return "Invalid 1 byte hexcode";
}

string checkTwoByteHexcode(string hexcode)
{

  string opcode = string(1, hexcode[0]) + hexcode[1];

  for (int i = 0; i < VALID_TWO_BYTE_OPCODES.size(); i++)
  {
    if (opcode == VALID_TWO_BYTE_OPCODES[i])
    {
      string register1 = string(1, hexcode[2]);
      string register2 = string(1, hexcode[3]);

      if (find(VALID_REGISTERS.begin(), VALID_REGISTERS.end(), stoi(register1)) != VALID_REGISTERS.end() && find(VALID_REGISTERS.begin(), VALID_REGISTERS.end(), stoi(register2)) != VALID_REGISTERS.end())
      {
        return "Valid 2 byte hexcode";
      }

      return "Invalid 2 byte hexcode, Invalid register";
      break;
    }
  }
  return "Invalid 2 byte hexcode, OPCODE does not exist";
}

string checkThreeByteHexcode(string hexcode)
{
  ll opcode = stoull(string(1, hexcode[0]) + hexcode[1], nullptr, 16) & 0xFC;
  string opcodeStr = to_string(opcode);

  if (find(VALID_THREE_OR_FOUR_BYTE_OPCODES.begin(), VALID_THREE_OR_FOUR_BYTE_OPCODES.end(), opcodeStr) != VALID_THREE_OR_FOUR_BYTE_OPCODES.end())
  {
    string binaryCode = convertHexToBin(hexcode);
    ll n = binaryCode[6] - '0';
    ll i = binaryCode[7] - '0';
    ll x = binaryCode[8] - '0';
    ll b = binaryCode[9] - '0';
    ll p = binaryCode[10] - '0';
    ll e = binaryCode[11] - '0';

    if (n == 0 && i == 0)
    {
      return "Valid 3 byte hexcode, Simple addressing mode";
    }
    else if (e == 1)
    {
      return "Invalid 3 byte opcode, e flag is set but it should be 0 for 3 byte opcode";
    }
    else if (b == 1 and p == 1)
    {
      return "Invalid 3 byte opcode, flag b and p cannot be 1 at the same time";
    }
    else if (n == 1 && i == 1)
    {
      return "Valid 3 byte opcode";
    }
    else if ((n == 1 && i == 0) || (n == 0 && i == 1))
    {
      if (x == 0)
      {
        return "Valid 3 byte opcode";
      }
      else
      {
        return "Invalid 3 byte opcode, X flag is SET, which is invalid for this mode of addressing";
      }
    }
    return "Valid 3 byte hexcode";
  }
  else
  {
    return "Invalid 3 byte hexcode, OPCODE does not exist";
  }
}

string checkFourByteHexcode(string hexcode)
{
  ll opcode = stoull(string(1, hexcode[0]) + hexcode[1], nullptr, 16) & 0xFC;
  string opcodeStr = to_string(opcode);

  if (find(VALID_THREE_OR_FOUR_BYTE_OPCODES.begin(), VALID_THREE_OR_FOUR_BYTE_OPCODES.end(), opcodeStr) != VALID_THREE_OR_FOUR_BYTE_OPCODES.end())
  {
    string binaryCode = convertHexToBin(hexcode);
    ll n = binaryCode[6] - '0';
    ll i = binaryCode[7] - '0';
    ll x = binaryCode[8] - '0';
    ll b = binaryCode[9] - '0';
    ll p = binaryCode[10] - '0';
    ll e = binaryCode[11] - '0';

    if (e != 1)
    {
      return "Invalid 4 byte opcode, E flag cannot be 0 for 4 byte opcode";
    }
    else if (n == 0 && i == 0)
      return "Invalid 4 byte opcode, N and I both cannot be 0 for 4 byte opcode";
    else if (b != 0)
      return "Invalid 4 byte opcode, B flag is SET which is invalid with this mode of addressing";
    else if (p != 0)
      return "Invalid 4 byte opcode, P flag is SET which is invalid with this mode of addressing";
    else if (x == 1)
    {
      if (n != 1 && i != 1)
        return "Invalid 4 byte opcode, N and I both cannot be 1 for 4 byte opcode";
    }
    return "Valid 4 byte opcode";
  }
  else
    return "Invalid 4 byte hexcode, OPCODE does not exist";
}

string check(string hexcode)
{
  if (hexcode.size() == 2)
  {
    return checkOneByteHexcode(hexcode);
  }
  else if (hexcode.size() == 4)
  {
    return checkTwoByteHexcode(hexcode);
  }
  else if (hexcode.size() == 6)
  {
    return checkThreeByteHexcode(hexcode);
  }
  else if (hexcode.size() == 8)
  {
    return checkFourByteHexcode(hexcode);
  }
  else
  {
    return "Invalid hexcode length";
  }
}

int main()
{
  // string s;
  // cout << "Enter the SIC code: ";
  // cin >> s;

  ifstream file("test_cases.txt");
  string line;

  if (file.is_open())
  {
    while (getline(file, line))
    {
      cout << "For test case: " << line << endl;
      cout << check(line) << endl;
      cout << "----------------------------------------------------------------" << endl;
    }
    file.close();
  }
  else
  {
    cout << "Unable to open file";
  }
}