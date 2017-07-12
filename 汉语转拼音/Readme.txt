C#����תƴ��(npinyin)������ת����ƴ��ȫ�Ļ�����ĸ
http://www.cnblogs.com/guohu/p/5018923.html

����תƴ��ò��һֱ��C#������һ�����⣬����ʲô��������һ����bug��֮ǰʹ�������ַ�����

1.Chinese2Spell.cs һЩ����ʶ��ĺ���ȫ��תΪZ

2.Microsoft Visual Studio International Feature Pack 1.0  ��"��"��������������ת��������ʧ����

 

��Щ����2010����ǰ�ķ��������ٻ��д�����Ϊ����תƴ������Ŭ���ţ�Ŀǰ�����������ľ���NPINYIN����googlecode���Կ������Ŀ�Դ��Ŀ��http://code.google.com/p/npinyin/

����ʶ����ֺ��٣����һ��ڲ���ά�����£������������Ƽ����ʹ�á�

���ص�ַ

dll��http://files.cnblogs.com/files/guohu/NPinyin-0.2.4588.20158-bin.zip

Դ�룺http://files.cnblogs.com/files/guohu/NPinyin-0.2.x-source_code.zip

 
v0.2.x�ı仯

    1�����ӶԲ�ͬ�����ʽ�ı���֧��,ͬʱ���ӱ���ת������Pinyin.ConvertEncoding
    2���ع����ַ�ƴ���Ļ�ȡ��δ�ҵ�ƴ��ʱ�����ַ�����.

��˼�� 2012��7��23����

������ת����ƴ��ȫ�ĺ�����ĸ��.net �����ʾ����

using System;
using System.Collections.Generic;
using System.Text;
using NPinyin;

namespace NPinyinTest
{
  class Program
  {
    static void Main(string[] args)
    {
      string[] maxims = new string[]{
        "�³�����Υ����������Ϊ",
        "�������ܳ����ģ�ǿ���Ǵ������",
        "��Ԧ���˵Ķ��Ƿܶ���������һ˿���룬������һ����ᣬ��ֹͣһ��Ŭ���� ",
        "�������ǰ���崵�ɽ�ң���������Զֻ������ˮһ̶", 
        "ų������ֻ����㲻ǰ��çײ����ֻ����Ϊ����ֻ�������¸ҵ��˲�����������"
      };

      string[] medicines = new string[] {
        "��άͪ����Һ",
        "����¶",
        "¯��ʯϴ��",
        "���������",
        "��ʯ֬���",
        "Īƥ�������",
        "��ù�����",
        "�⻯�ɵ������",
        "�����ε����",
        "�����������",
        "˫�ȷ�����Ұ����",
        "������",
        "��ù�����",
        "�ر��η����",
        "̪�������",
        "�俵����ࡢ˨��",
        "������˨",
        "����ݭ����˨"
      };

      Console.WriteLine("UTF8����ƴ����");
      foreach (string s in maxims)
      {
        Console.WriteLine("���֣�{0}\nƴ����{1}\n", s, Pinyin.GetPinyin(s));
      }

      Encoding gb2312 = Encoding.GetEncoding("GB2312");
      Console.WriteLine("GB2312ƴ�����룺");
      foreach (string m in medicines)
      {
        string s = Pinyin.ConvertEncoding(m, Encoding.UTF8, gb2312);
        Console.WriteLine("ҩƷ��{0}\n���룺{1}\n", s, Pinyin.GetInitials(s, gb2312));
      }

      Console.ReadKey();
    }
  }
}

���н��

UTF8����ƴ���� ���֣��³�����Υ����������Ϊ ƴ����shi chang yu ren wei �� shi zong zai ren wei

���֣��������ܳ����ģ�ǿ���Ǵ������ ƴ����jun ma shi pao chu lai de �� qiang bing shi da chu lai de

���֣���Ԧ���˵Ķ��Ƿܶ���������һ˿���룬������һ����ᣬ��ֹͣһ��Ŭ���� ƴ����jia yu ming yun de duo shi fen dou �� bu bao you yi si huan xiang �� bu fa ng qi yi dian ji hui �� bu ting zhi yi ri nu li ��

���֣��������ǰ���崵�ɽ�ң���������Զֻ������ˮһ̶ ƴ����ru guo ju pa qian mian die dang de shan yan �� sheng ming jiu yong yuan zh i neng shi si shui yi tan

���֣�ų������ֻ����㲻ǰ��çײ����ֻ����Ϊ����ֻ�������¸ҵ��˲����������� ƴ����nuo ruo de ren zhi hui guo zu bu qian �� mang zhuang de ren zhi neng yin w ei shao shen �� zhi you zhen zheng yong gan de ren cai neng suo xiang pi mi

GB2312ƴ�����룺 ҩƷ����άͪ����Һ ���룺JWTDRY

ҩƷ������¶ ���룺KSL

ҩƷ��¯��ʯϴ�� ���룺LGSXJ

ҩƷ����������� ���룺BZLAT

ҩƷ����ʯ֬��� ���룺YSZRG

ҩƷ��Īƥ������� ���룺MPLXRG

ҩƷ����ù����� ���룺HMSRG
 

ҩƷ���⻯�ɵ������ ���룺QHKDSRG

ҩƷ�������ε���� ���룺QANDRG

ҩƷ������������� ���룺DBQSRG

ҩƷ��˫�ȷ�����Ұ���� ���룺SLFSEYARG

ҩƷ�������� ���룺DCG

ҩƷ����ù����� ���룺KMZRG

ҩƷ���ر��η���� ���룺TBNFRG

ҩƷ��̪������� ���룺TDARG

ҩƷ���俵����ࡢ˨�� ���룺MKZRG��SJ

ҩƷ��������˨ ���룺JXZS

ҩƷ������ݭ����˨ ���룺FFESYS