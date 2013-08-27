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
package com.the9.master.shell.utils
{
	import flash.display.BitmapData;
	import flash.display.Shape;
	
	import starling.display.Image;
	import starling.textures.Texture;
	
	/**
	 * 场景工具集
	 * @author lvxiangsong
	 */
	public class SceneUtil
	{
		
		public function SceneUtil()
		{
		}
		
		
		/**
		 * 创建纯色背景，注意在必要的地方dispose掉
		 * @param color 颜色
		 * @param alpha 透明度
		 * @param fullScreen 是否全屏
		 * @return 
		 */
		public static function createColorScene(color:uint = 0x000000, alpha:Number = 1.0, fullScreen:Boolean = true):Image
		{
			
			var shape:Shape = new Shape();
			shape.graphics.beginFill(color, alpha);
			var bmpt:BitmapData = null;
			if (fullScreen)
			{
				shape.graphics.drawRect(0, 0, GameConst.fullSceenWidth, GameConst.fullSceenHeght);
				bmpt = new BitmapData(GameConst.fullSceenWidth, GameConst.fullSceenHeght, true, 0x0);
			}
			else
			{
				shape.graphics.drawRect(0, 0, GameConst.gameWidth, GameConst.gameHeight);
				bmpt = new BitmapData(GameConst.gameWidth, GameConst.gameHeight, true, 0x0);
			}
			shape.graphics.endFill();
			bmpt.draw(shape);
			var img:Image = new Image(Texture.fromBitmapData(bmpt));
			
			if (fullScreen)
			{
				img.x = -GameConst.viewPortX / GameConst.scale;
				img.y = -GameConst.viewPortY / GameConst.scale;
			}
			bmpt.dispose();
			return img;
		}
		
		
		
	}
}