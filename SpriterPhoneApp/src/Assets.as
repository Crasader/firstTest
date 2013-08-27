////////////////////////////////////////////////////////////
// 名称: 
// 作者: lvxiangsong
// 日期: Aug 27, 2013
// 功能: 
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      Aug 27, 2013
////////////////////////////////////////////////////////////
package
{
	import starling.utils.AssetManager;
	
	/**
	 * 资源管理
	 * @author lvxiangsong
	 */
	public class Assets extends AssetManager
	{
		[Embed(source="media/Ubuntu-R.ttf", embedAsCFF="false", fontFamily="Ubuntu")]
		private static const UbuntuRegular:Class;
		
		private static var _instance:Assets;
		
		/** 加载完毕回调 */
		private var _compCall:Function;
		
		public function Assets()
		{
		}
		
		public static function get instance():Assets
		{
			if (_instance == null)
				_instance = new Assets();
			return _instance;
		}
		
		public function start(compCall:Function):void
		{
			_compCall = compCall;
			_instance.verbose = true;
			
			_instance.enqueue("media/SpriterTexturePacker.png");
			_instance.enqueue("media/SpriterTexturePacker.xml");
			_instance.enqueue("media/orc.scml");
			_instance.enqueue("media/mage.scml");
			_instance.enqueue("media/desyrel.png");
			_instance.enqueue("media/desyrel.fnt");
			_instance.enqueue("media/asst.png");
			_instance.enqueue("media/asst.xml");
			
			_instance.loadQueue(onProgress);
			
		}
		
		private function onProgress(radio:Number):void
		{
			if (radio >= 1 && _compCall != null)
			{
				Log.log("加载完毕，进入游戏");
				_compCall.call();
				_compCall = null;
			}
		}
	}
}