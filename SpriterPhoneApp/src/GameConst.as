// 文件名：
// 功能：
// 日期：2013-8-27
// 版本：
// 		作者                   日期               内容
//		lxsong             2013-8-27

package
{
	import flash.system.Capabilities;
	
	/**
	 * 
	 * @author lxsong
	 */
	public class GameConst
	{
		//游戏参数 
		public static const aspect_ratio:Number = 960/640;
		public static var stageWidth:uint = 960;
		public static var stageHeight:uint = 640;
		public static const gameWidth:uint = 960;
		public static const gameHeight:uint = 640;
		public static var viewPortX:int = 0;
		public static var viewPortY:int = 0;
		//拉伸
		public static var isRetina:Boolean = false;
		public static var gameIsPlay:Boolean = false;
		public static var scale:Number;
		public static var scaleSence:Number;
		public static var speed:Number = 1;
		public static var isARM:Boolean = Capabilities.cpuArchitecture == "ARM";
		
		public static var fullSceenWidth:Number = 960;
		public static var fullSceenHeght:Number = 640;
		
		public function GameConst()
		{
		}
	}
}
