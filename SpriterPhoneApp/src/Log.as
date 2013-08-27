// 文件名：
// 功能：
// 日期：2013-8-27
// 版本：
// 		作者                   日期               内容
//		lxsong             2013-8-27

package
{
	
	
	/**
	 * 
	 * @author lxsong
	 */
	public class Log
	{
		public function Log()
		{
		}
		
		public static function log(mes:String,moduleName:String = "All"):void
		{
			trace("log:"+mes);
		}
		
		public static function warning(mes:String,moduleName:String = "All"):void
		{
			trace("warning:"+mes);
		}
		
		public static function error(mes:String,moduleName:String = "All"):void
		{
			trace("error:"+mes);
		}
	}
}
