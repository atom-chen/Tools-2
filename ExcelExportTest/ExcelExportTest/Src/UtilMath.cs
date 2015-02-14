﻿namespace SDK.Common
{
    public class UtilMath
    {
        // 获取一个最近的大小
        static public uint getCloseSize(uint needSize, uint capacity, uint maxCapacity)
        {
            uint ret = 0;
            if (capacity >= needSize)
            {
                ret = capacity;
            }
            else
            {
                ret = 2 * capacity;
                while (ret < needSize && ret < maxCapacity)
                {
                    ret *= 2;
                }

                if (ret > maxCapacity)
                {
                    ret = maxCapacity;
                }
            }

            return ret;
        }
    }
}