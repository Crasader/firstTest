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
	import com.the9.master.shell.utils.SceneUtil;
	import com.the9.master.shell.utils.SpriterClipUtil;
	
	import flash.utils.getTimer;
	
	import starling.animation.Juggler;
	import starling.core.Starling;
	import starling.display.Image;
	import starling.display.MovieClip;
	import starling.events.Event;
	import starling.text.TextField;
	
	import treefortress.spriter.SpriterClip;
	
	
	/**
	 * 
	 * @author lvxiangsong
	 */
	public class GameLayer extends BaseLayer
	{
		private var jugger:Juggler;
		
		public function GameLayer()
		{
			super();
			jugger = new Juggler();
			doSomething();
		}
		
		override protected function initSelf():void
		{
			super.initSelf();
			
			var bg:Image = SceneUtil.createColorScene(0x00ff00, 0.5, false);
			addChild(bg);
		}
		
		private function doSomething():void
		{
			var arr:Array = ["idle", "run", "attack", "dead", "dance", "attackDown", "attackUp", "hit"];// 
			for (var i:int = 0; i < 200; i++)
			{
				var mage:SpriterClip = SpriterClipUtil.createSpriterClip("mage", "SpriterTexturePacker");
				if (mage)
				{
					mage.play(arr[int(Math.random() * 8)]); // 
					mage.scaleX = mage.scaleY = 0.5;
					mage.playbackSpeed = Math.random() * 3 + 0.1;
					mage.x = 800 * Math.random() + 100;
					mage.y = 430 * Math.random() + 100;
					addChild(mage);
					jugger.add(mage);
				}
			}
			
//			Starling.juggler.add(jugger);
			addEventListener(Event.ENTER_FRAME, onFrame);
			
//			for (var i:int = 0; i < 100; i++)
//			{
//				var m:MovieClip = new MovieClip(Assets.instance.getTextures("player"), int(24 * Math.random()) + 1);
//				m.x = Math.random() * 500;
//				m.y = Math.random() * 300;
//				addChild(m);
//				Starling.current.juggler.add(m);
//			}
			
			var txt:TextField = new TextField(300, 40, "hello every one", "Ubuntu", 19);
			addChild(txt);
			
		}
		
		private function onFrame(evt:Event):void
		{
			var start:int = getTimer();
			jugger.advanceTime(Number(evt.data));
			trace(getTimer() - start);
		}
		
		
	}
}