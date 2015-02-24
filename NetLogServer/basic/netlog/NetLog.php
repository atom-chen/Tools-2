<?php

/**
 * @brief 将日志写入服务器
 * */

<?php

use yii\db\Connection;

// 宕机存储
require(__DIR__ . '/../vendor/autoload.php');				// 导入自动加载机制
require(__DIR__ . '/../vendor/yiisoft/yii2/Yii.php');		// 导入全局

$config = require(__DIR__ . '/../config/cpconfig.php');		// 导入配置
// 开启日志功能
//new yii\web\Application($config); 

$basicCfg = require(__DIR__ . '/BasicCfg.php');
$platformCfg = require(__DIR__ . '/PlatformCfg.php');

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
$swfversion = $_REQUEST['swfversion'];
$error = $_REQUEST['error'];
$curtime = date("Y-m-d H:i:m");

$cursql = 'SELECT `cnt` FROM `cpcount` WHERE `id`=' . $platformid . ';';
$dataTableName = date("Y-m") . "-cpdata"; 

// 建立数据库连接
$connection = new Connection([
		     'dsn' => $config['components']['db']['dsn'],
		     'username' => $config['components']['db']['username'],
		     'password' => $config['components']['db']['password']
		 ]);
$connection->open();

// 检查数据库中记录数
$cntcmd = $connection->createCommand($cursql);
$retset = $cntcmd->queryOne();
if($retset)	// 查询有数据
{
	if(isset($retset['cnt']))
	{
		//if($retset['cnt'] < $basicCfg['maxcount'])		// 允许保存的最大日志数
		//{
			// 执行插入操作
			//$cursql = 'insert into `cpdata` values (' . $charid . ', "' . $name . '", ' . $type . ', ' . ' "' .$platform . '", ' . $version . ', "' . $error . '");';
			//$insertcmd = $connection->createCommand($cursql);
			//$insertcmd->execute();
			$insertcmd = $connection->createCommand();
			$insertcmd->insert($dataTableName, [
										'charid' => $charid,
										'name' => $name,
										'time' => $curtime,
										'type' => $type,
										'platform' => $platform,
										'version' => $version,
										'swfversion' => $swfversion,
										'error' => $error
									]
							)->execute();
			
			// 更新计数
			//$cursql = 'update `cpcount` set `cnt`=' . ($retset['cnt'] + 1) . ' where `id`=' . $platformid;
			//$updatecmd = $connection->createCommand($cursql);
			//$updatecmd->execute();
			$condition = '`id`=' . $platformid;
			$updatecmd = $connection->createCommand();
			$updatecmd->update('cpcount',[
										'cnt' => ($retset['cnt'] + 1)
								],
								$condition
						)->execute();
		//}
	}
}
else 	// 第一次没有数据
{
	// 执行插入操作
	//$cursql = 'insert into `cpdata` values (' . $charid . ', "' . $name . '", ' . $type . ', ' . ' "' .$platform . '", ' . $version . ', "' . $error . '");';
	//$insertcmd = $connection->createCommand($cursql);
	//$insertcmd->execute();
	$insertcmd = $connection->createCommand();
	$insertcmd->insert($dataTableName, [
			'charid' => $charid,
			'name' => $name,
			'time' => $curtime,
			'type' => $type,
			'platform' => $platform,
			'version' => $version,
			'swfversion' => $swfversion,
			'error' => $error
			]
	)->execute();
		
	// 执行插入操作
	//$cursql = 'insert into `cpcount` values (' . $platformid . ', ' . 1 . ');';
	//$updatecmd = $connection->createCommand($cursql);
	//$updatecmd->execute();
	$updatecmd = $connection->createCommand();
	$updatecmd->insert('cpcount', [
			'id' => $platformid,
			'cnt' => 1
			]
	)->execute();
}



