#-*- encoding=utf-8 -*-

'''
@brief: UtilTime
'''

import time;
from Libs.Core.GObject import GObject;

class UtilTime(GObject):

    @staticmethod
    def sleep(seconds):
        time.sleep(seconds);

    
    # 获取 epoch（1970 年 1 月 1 日 00:00:00）开始到当前的秒数。
    @staticmethod
    def time():
        return time.time();


    # localtime返回tuple格式的时间，localtime返回的是当前时区的值。
    @staticmethod
    def localtime():
        return time.localtime();
    
    
    # gmtime()，gmtime()返回的是0时区的值
    @staticmethod
    def gmtime():
        return time.gmtime();
    
    
    # 前时区和0时区相差的秒数
    @staticmethod
    def timezone():
        return time.timezone;


    '''
          返回格式化时间
    python中时间日期格式化符号：
    %y 两位数的年份表示（00-99）
    %Y 四位数的年份表示（000-9999）
    %m 月份（01-12）
    %d 月内中的一天（0-31）
    %H 24小时制小时数（0-23）
    %I 12小时制小时数（01-12）
    %M 分钟数（00=59）
    %S 秒（00-59）
    %a 本地简化星期名称
    %A 本地完整星期名称
    %b 本地简化的月份名称
    %B 本地完整的月份名称
    %c 本地相应的日期表示和时间表示
    %j 年内的一天（001-366）
    %p 本地A.M.或P.M.的等价符
    %U 一年中的星期数（00-53）星期天为星期的开始
    %w 星期（0-6），星期天为星期的开始
    %W 一年中的星期数（00-53）星期一为星期的开始
    %x 本地相应的日期表示
    %X 本地相应的时间表示
    %Z 当前时区的名称
    %% %号本身 
    '''
    @staticmethod
    def strftime(formatStr, timeTuple):
        return time.strftime(formatStr, timeTuple);
        

    @staticmethod
    def getTimeStamp():
        return UtilTime.strftime('%Y-%m-%d-%H-%M-%S',time.localtime(time.time()));

