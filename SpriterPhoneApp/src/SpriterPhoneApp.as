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
	import flash.desktop.NativeApplication;
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.geom.Rectangle;
	import flash.system.Capabilities;
	
	import starling.core.Starling;
	import starling.events.Event;
	
	
	/**
	 * 
	 * @author lvxiangsong
	 */
	public class SpriterPhoneApp extends Sprite
	{
		private var mStarling:Starling;
		
		public function SpriterPhoneApp()
		{
			super();
			
			// support autoOrients
			stage.align = StageAlign.TOP_LEFT;
			stage.scaleMode = StageScaleMode.NO_SCALE;
			
			// ARM 为 安卓 x86 计算机 
			Log.log("cpuArchitecture:"+Capabilities.cpuArchitecture);
			
			Log.log("playerType"+Capabilities.playerType);
			
			Log.log("manufacturer:"+Capabilities.manufacturer);
			
			//开启多点触控
			Starling.multitouchEnabled = true;
			//是否启用 “丢失内容修复功能 ”.在某些系统中，
			if(Capabilities.manufacturer.indexOf("iOS") != -1)
			{
				Starling.handleLostContext = false;
			}
			else if(Capabilities.manufacturer.indexOf("Android") != -1)
			{
				Starling.handleLostContext = true;
			}
			else
			{
				Starling.handleLostContext = true;
			}
			
			//创建一个适应于屏幕大小的渲染区域
			var screenWidth:int = stage.fullScreenWidth;
			var screenHeight:int = stage.fullScreenHeight;
			// 场景全屏
			if (screenWidth / screenHeight > GameConst.aspect_ratio)
			{
				GameConst.stageWidth = screenWidth;
				GameConst.stageHeight = int(GameConst.stageWidth / GameConst.aspect_ratio);
			}
			else
			{
				GameConst.stageHeight = screenHeight;
				GameConst.stageWidth = int(GameConst.stageHeight * GameConst.aspect_ratio);	
				
			}
			GameConst.scaleSence =  GameConst.stageHeight/640;
			//内部全屏
			if (screenWidth / screenHeight > GameConst.aspect_ratio)
			{
				GameConst.stageHeight = screenHeight;
				GameConst.stageWidth = int(GameConst.stageHeight * GameConst.aspect_ratio);
				GameConst.viewPortX = int((screenWidth - GameConst.stageWidth) / 2);
			}
			else
			{
				GameConst.stageWidth = screenWidth;
				GameConst.stageHeight = int(GameConst.stageWidth / GameConst.aspect_ratio);
				GameConst.viewPortY = int((screenHeight - GameConst.stageHeight) / 2);
			}
			GameConst.scale  = GameConst.stageHeight/640;
			
			GameConst.fullSceenWidth = Math.max(screenWidth, GameConst.gameWidth / GameConst.scale);
			GameConst.fullSceenHeght = Math.max(screenHeight, GameConst.gameHeight / GameConst.scale);
			
			//启动Starling
			mStarling = new Starling(Game, stage, new Rectangle(0, 0,screenWidth, screenHeight), null, "auto", "baseline");
			
			if (GameConst.isRetina)
			{
				this.mStarling.stage.stageWidth = GameConst.stageWidth;
				this.mStarling.stage.stageHeight = GameConst.stageHeight;
			}
			this.mStarling.simulateMultitouch = false;
			this.mStarling.enableErrorChecking = false;
			this.mStarling.showStats = true;
			this.mStarling.addEventListener(starling.events.Event.ROOT_CREATED, function (param1:Object, param2:Game) : void
			{
				mStarling.removeEventListener(starling.events.Event.ROOT_CREATED, arguments.callee);
				mStarling.start();
				stage.frameRate = 60;				
				return;
			});
			
			if (GameConst.isARM || Capabilities.playerType == "Desktop")
			{
				NativeApplication.nativeApplication.systemIdleMode = "keepAwake";
				NativeApplication.nativeApplication.addEventListener(flash.events.Event.ACTIVATE, function (e:flash.events.Event) : void
				{
					mStarling.start();
					stage.frameRate = 60;
					return;
				});
				
				NativeApplication.nativeApplication.addEventListener(flash.events.Event.DEACTIVATE, function (e:flash.events.Event) : void
				{
					mStarling.stop();
					stage.frameRate = 0;
					return;
				});
			}	
		}
	}
}