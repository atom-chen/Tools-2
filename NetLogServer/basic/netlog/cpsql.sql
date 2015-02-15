-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.5.35-MariaDB-log - mariadb.org binary distribution
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  8.3.0.4694
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- 导出 crashreport 的数据库结构
-- DROP DATABASE IF EXISTS `clientcrashreport`;
CREATE DATABASE IF NOT EXISTS `clientcrashreport` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `clientcrashreport`;


-- 导出  表 crashreport.cpdata 结构
-- DROP TABLE IF EXISTS `cpdata`;
CREATE TABLE IF NOT EXISTS `cpdata` (
  -- `id` int(20) unsigned zerofill NOT NULL PRIMARY KEY,
  `charid` int(20) unsigned NOT NULL DEFAULT '0',
  `name` char(255) NOT NULL DEFAULT '0',
  `time` char(255) NOT NULL DEFAULT '0',
  `type` int(20) unsigned NOT NULL DEFAULT '0',
  `platform` char(255) NOT NULL DEFAULT '0',
  `version` int(20) unsigned NOT NULL DEFAULT '0',
  `swfversion` char(255) NOT NULL DEFAULT '0',
  -- `error` TEXT NOT NULL DEFAULT ''
  `error` TEXT NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- 导出  表 crashreport.cpcount 结构
-- DROP TABLE IF EXISTS `cpcount`;
CREATE TABLE IF NOT EXISTS `cpcount` (
  `id` int(20) unsigned NOT NULL PRIMARY KEY,
  `cnt` int(20) unsigned NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

