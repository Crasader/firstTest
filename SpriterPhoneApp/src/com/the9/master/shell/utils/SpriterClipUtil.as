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
	import starling.textures.TextureAtlas;
	
	import treefortress.spriter.AnimationSet;
	import treefortress.spriter.SpriterClip;
	
	/**
	 * SpriterClip工具
	 * @author lvxiangsong
	 */
	public class SpriterClipUtil
	{
		public function SpriterClipUtil()
		{
		}
		
		/**
		 * 创建一个SpriterClip
		 * @param scmlName scml文件名
		 * @param textureName 素材文件名
		 * @param scale 缩放比
		 * @return 
		 */
		public static function createSpriterClip(scmlName:String, textureName:String, scale:Number = 1.0):SpriterClip
		{
			var texture:TextureAtlas = Assets.instance.getTextureAtlas(textureName);
			if (texture == null)
			{
				return null;
			}
			var animation:AnimationSet = new AnimationSet(Assets.instance.getScml(scmlName), scale, scmlName);
			if (animation == null)
			{
				return null;
			}
			return new SpriterClip(animation, texture);
		}
		
		
	}
}