// 文件名：
// 功能：
// 日期：2013-8-27
// 版本：
// 		作者                   日期               内容
//		lxsong             2013-8-27

package
{
	import com.the9.master.shell.layer.GameLayer;
	
	import starling.display.Sprite;
	
	
	/**
	 * 
	 * @author lvxiangsong
	 */
	public class Game extends Sprite
	{
		private var _gameLayer:GameLayer;
		
		public function Game()
		{
			super();
			
			loadAsset();
		}
		
		/**
		 * 加载素材
		 */
		private function loadAsset():void
		{
			Assets.instance.start(function comp():void{
				initLayers();
			});
		}
		
		/**
		 * 初始化游戏层
		 */
		private function initLayers():void
		{
			_gameLayer = new GameLayer();
			addChild(_gameLayer);
		}
	}
}
