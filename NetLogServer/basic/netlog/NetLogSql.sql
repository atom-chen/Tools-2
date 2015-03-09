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

-- 导出 netlog 的数据库结构
-- DROP DATABASE IF EXISTS `netlog`;
CREATE DATABASE IF NOT EXISTS `netlog` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `netlog`;


-- 导出  表 netlog.netlogdata 结构
-- DROP TABLE IF EXISTS `netlogdata`;
CREATE TABLE IF NOT EXISTS `netlogdata` (
  -- `id` int(20) unsigned zerofill NOT NULL PRIMARY KEY,
  `charid` int(20) unsigned NOT NULL DEFAULT '0',
  `name` char(255) NOT NULL DEFAULT '0',
  `time` char(255) NOT NULL DEFAULT '0',
  `type` int(20) unsigned NOT NULL DEFAULT '0',
  `platform` char(255) NOT NULL DEFAULT '0',
  `version` int(20) unsigned NOT NULL DEFAULT '0',
  -- `error` TEXT NOT NULL DEFAULT ''
  `error` TEXT NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- 导出  表 netlog.netlogcount 结构
-- DROP TABLE IF EXISTS `netlogcount`;
CREATE TABLE IF NOT EXISTS `netlogcount` (
  `id` int(20) unsigned NOT NULL PRIMARY KEY,
  `cnt` int(20) unsigned NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

