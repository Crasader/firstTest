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
package com.the9.master.shell.layer
{
	import starling.display.Sprite;
	
	
	/**
	 * 
	 * @author lvxiangsong
	 */
	public class BaseLayer extends Sprite
	{
		public function BaseLayer()
		{
			super();
			initSelf();
		}
		
		/**
		 * 初始化自己
		 */
		protected function initSelf():void
		{
			if (!GameConst.isRetina)
			{
				this.x = GameConst.viewPortX;
				this.y = GameConst.viewPortY;
				this.scaleX = this.scaleY = GameConst.scale;
			}
			else
			{
				this.scaleX = this.scaleY = GameConst.scaleSence;
			}
		}
		
	}
}