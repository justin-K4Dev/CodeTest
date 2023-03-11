using System;
using System.Runtime.InteropServices; // 관리되지않는 코드(포인터 사용및 구조체를 직렬화하기 위해)
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;


namespace ProtoBuf.Net.Unity
{
    public class Utility
    {
        // 바이트 버퍼 데이터를 객체 데이터로 변환 (boxing)
        public static void copyPtrToObject(ref byte[] arbtBuff, ref object objPacket, int iOffSet)
        {
            unsafe
            {
                fixed (byte* ptrBuff = arbtBuff)
                {
                    Marshal.PtrToStructure((IntPtr)(ptrBuff + iOffSet), objPacket);
                }
            }
        }

        // 객체 데이터를 바이트 버퍼 데이터로 변환 (unboxing)
        public static void copyObjectToPtr(ref object objPacket, ref byte[] arbtBuff, int iOffSet)
        {
            unsafe
            {
                fixed (byte* ptrBuff = arbtBuff)
                {
                    Marshal.StructureToPtr(objPacket, (IntPtr)(ptrBuff + iOffSet), true);
                }
            }
        }

        // 날짜 형식의 데이타를 int형으로 형변환
        public static int convertDateTimeToInt(System.DateTime dt)
        {
            System.TimeSpan ts = dt.Subtract(new System.DateTime(1970, 1, 1));
            return (int)(ts.Ticks / 10000000L);
        }

        // int형식의 데이타를 날짜형으로 형 변환
        public static DateTime convertIntToDateTime(int iTimeTickCount)
        {
            System.DateTime dt = new DateTime(1970, 1, 1).AddSeconds(iTimeTickCount);
            return dt;
        }

    }
}
