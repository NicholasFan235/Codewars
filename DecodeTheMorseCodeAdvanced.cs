using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;

public class MorseCodeDecoder
{
    public static Dictionary<int, int> lengthFreq;
    public static int dt;

    public static void FT(string bits){
        lengthFreq = new Dictionary<int, int>();
        int ctr = 0;
        char curr = bits[0];
        for (int i = 0; i < bits.Length; i++){
            if (curr.Equals(bits[i])){
                ctr++;
            }
            else{
                if (!lengthFreq.ContainsKey(ctr)) lengthFreq[ctr] = 0;
                lengthFreq[ctr]++;
                ctr = 1;
                curr = bits[i];
            }
        }
        if (!lengthFreq.ContainsKey(ctr)) lengthFreq[ctr] = 0;
        lengthFreq[ctr]++;
    }

    public static void GetDT(){
        int maxCount1 = 0, maxCount2 = 0;
        int maxi1 = 0, maxi2 = 0;
        foreach (var item in lengthFreq){
            //Console.WriteLine("{0}: {1}", item.Key, item.Value);
            if (item.Value > maxCount1){
                maxCount2 = maxCount1;
                maxi2 = maxi1;
                maxCount1 = item.Value;
                maxi1 = item.Key;
            }
            if (item.Value > maxCount2 && item.Key != maxi1){
                maxCount2 = item.Value;
                maxi2 = item.Key;
            }
        }
        //Console.WriteLine("{0} and {1}", maxi1, maxi2);
        if (maxi1 > maxi2) dt = maxi1/3;
        else dt = maxi1;
    }

    public static string DecodeBits(string bits)
    {
        Console.WriteLine(bits);
        char[] trimChars = {'0'};
        bits = bits.Trim(trimChars);
        FT(bits);
        GetDT();

        string tspace = "";
        for (int i = 0; i < 7*dt; i++){
            tspace += '0';
        }
        string nextchar = "";
        for (int i = 0; i < 3*dt; i++){
            nextchar += '0';
        }
        string nextel = "";
        for (int i = 0; i < dt; i++){
            nextel += '0';
        }
        string dash = "";
        for (int i = 0; i < 3*dt; i++){
            dash += '1';
        }
        string dot = "";
        for (int i = 0; i < dt; i++){
            dot += '1';
        }

        bits = bits.Replace(dash, "-");
        bits = bits.Replace(dot, ".");
        bits = bits.Replace(tspace, "   ");
        bits = bits.Replace(nextchar, " ");
        bits = bits.Replace(nextel, "");
        return bits;
    }

    public static string DecodeMorse(string morseCode)
    {
        Console.WriteLine(morseCode);
        string decoded = "";
        string word = "";
        int start = -1;
        while (morseCode[++start].Equals(' '));
        int end = morseCode.Length;
        while (morseCode[--end].Equals(' '));

        for (int i = start; i <= end; i++){
            char c = morseCode[i];
            if (c.Equals(' ')){
                if (word.Equals("")){
                    decoded += ' ';
                    i++;
                    continue;
                }
                else{
                    // decode word
                    decoded += MorseCode.Get(word);
                    // reset word
                    word = "";
                }
            }
            else{
                word += c;
            }
        }
        decoded += MorseCode.Get(word);
        return decoded;
    }
}