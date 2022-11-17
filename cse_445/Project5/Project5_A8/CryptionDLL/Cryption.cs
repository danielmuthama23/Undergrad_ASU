using System.Text;

namespace CryptionDLL
{
    public class Cryption
    {
        public static string Encrypt(string plainString)
        {
            byte[] bytes = Encoding.ASCII.GetBytes(plainString);
            
            string encrypted = "";
            foreach (byte b in bytes)
                encrypted += b;

            return encrypted;
        }

        public static string Decrypt(string encryptedString)
        {
            IEnumerable<string> arr = Enumerable
                .Range(0, encryptedString.Length / 3)
                .Select(i => encryptedString.Substring(i*3, 3));
            List<byte> byteArr = new List<byte>();
            string[] strArr = arr.ToArray();

            int[] parsedInts = Array.ConvertAll(strArr, int.Parse);

            foreach (int i in parsedInts)
                byteArr.Add((byte)i);

            return Encoding.Default.GetString(byteArr.ToArray<byte>());
        }
    }
}