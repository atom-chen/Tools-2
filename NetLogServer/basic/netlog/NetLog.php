<?php

/**
 * @brief 将日志写入服务器
 * */

use yii\db\Connection;

// 宕机存储
require(__DIR__ . '/../vendor/autoload.php');				// 导入自动加载机制
require(__DIR__ . '/../vendor/yiisoft/yii2/Yii.php');		// 导入全局

$config = require(__DIR__ . '/../config/NetLogConfig.php');		// 导入配置
// 开启日志功能
//new yii\web\Application($config); 

$basicCfg = require(__DIR__ . '/BasicCfg.php');

// 获取参数
if(!isset($_REQUEST['error']))
{
	exit();
}

$platformid = $_REQUEST['id'];

$charid = $_REQUEST['charid'];
$name = $_REQUEST['name'];
$type = $_REQUEST['type'];
$platform = $_REQUEST['platform'];
$version = $_REQUEST['version'];
$error = $_REQUEST['error'];
$curtime = date("Y-m-d H:i:m");

$platformid = 1000;
$charid = 1000;
$name = "aaaa";
$type = 1000;
$platform = "aaa";
$version = 10000;
//$error = "您好";
$curtime = "18:45:52";

$cursql = 'SELECT `cnt` FROM `netlogcount` WHERE `id`=' . $platformid . ';';
//$dataTableName = date("Y-m") . "-netlogdata";
$dataTableName = "netlogdata"; 

// 建立数据库连接
$connection = new Connection([
		     'dsn' => $config['components']['db']['dsn'],
		     'username' => $config['components']['db']['username'],
		     'password' => $config['components']['db']['password']
		 ]);
$connection->charset = 'utf8';		// 这个字符集在 NetLogDB.php 中的配置不能赋值到这里
$connection->open();

// 检查数据库中记录数
$cntcmd = $connection->createCommand($cursql);
$retset = $cntcmd->queryOne();
if($retset)	// 查询有数据
{
	if(isset($retset['cnt']))
	{
		// 执行插入操作
		$insertcmd = $connection->createCommand();
		$insertcmd->insert($dataTableName, [
									'charid' => $charid,
									'name' => $name,
									'time' => $curtime,
									'type' => $type,
									'platform' => $platform,
									'version' => $version,
									'error' => $error
								]
						)->execute();
		
		// 更新计数
		$condition = '`id`=' . $platformid;
		$updatecmd = $connection->createCommand();
		$updatecmd->update('netlogcount',[
									'cnt' => ($retset['cnt'] + 1)
							],
							$condition
					)->execute();
	}
}
else 	// 第一次没有数据
{
	// 执行插入操作
	$insertcmd = $connection->createCommand();
	$insertcmd->insert($dataTableName, [
			'charid' => $charid,
			'name' => $name,
			'time' => $curtime,
			'type' => $type,
			'platform' => $platform,
			'version' => $version,
			'error' => $error
			]
	)->execute();
		
	// 执行插入操作
	$updatecmd = $connection->createCommand();
	$updatecmd->insert('netlogcount', [
			'id' => $platformid,
			'cnt' => 1
			]
	)->execute();
}



