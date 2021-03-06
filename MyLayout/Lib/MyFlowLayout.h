//
//  MyFlowLayout.h
//  MyLayout
//
//  Created by oybq on 15/10/31.
//  Copyright (c) 2015年 YoungSoft. All rights reserved.
//

#import "MyBaseLayout.h"


@interface UIView(MyFlowLayoutExt)

/**
 *流式布局子视图的尺寸的比重，默认值是0。这个属性的意义根据浮动布局视图的方向而不同。
 *当流式布局是垂直流式布局，这个属性用来设置子视图宽度占用当前行的剩余宽度的比重，这样子视图就不需要明确的设定宽度值。
 *当流式布局是水平流式布局，这个属性用来设置子视图高度占用当前列的剩余高度的比重，这样子视图就不需要明确的设定高度值。
 *需要注意的是数量约束和内容约束两种布局中的weight的概念有一定的差异：
    前者的真实尺寸值 = 剩余尺寸 * 当前子视图的比重/(子视图所在行的所有比重之和)。
    后者的真实尺寸值 = 剩余尺寸 *当前子视图的比重。
 举例来说，假设垂直布局视图的宽度是100，而当前视图的前面一个视图已经占据了20的宽度，那么当设置当前视图的weight为1时则当前视图的宽度就会被设定为80。
 到一个新的行的。而如果设定为0.8则当前视图的宽度则为(100-20)*0.8 = 64了。

 */
@property(nonatomic, assign)  CGFloat weight;

@end

/**
 *流式布局是一种里面的子视图按照添加的顺序依次排列，当遇到某种约束限制后会另起一行再重新排列的多行多列展示的布局视图。这里的约束限制主要有数量约束限制和内容尺寸约束限制两种，而换行的方向又分为垂直和水平方向，因此流式布局一共有垂直数量约束流式布局、垂直内容约束流式布局、水平数量约束流式布局、水平内容约束流式布局。流式布局主要应用于那些有规律排列的场景，在某种程度上可以作为UICollectionView的替代品。
 1.垂直数量约束流式布局
 orientation为MyLayoutViewOrientation_Vert,arrangedCount不为0,支持wrapContentHeight,支持wrapContentWidth,不支持autoArrange。

 2.垂直内容约束流式布局.
    orientation为MyLayoutViewOrientation_Vert,arrangedCount为0,支持wrapContentHeight,不支持wrapContentWidth,支持autoArrange。
 
 
 3.水平数量约束流式布局。
 orientation为MyLayoutViewOrientation_Horz,arrangedCount不为0,支持wrapContentHeight,支持wrapContentWidth,不支持autoArrange。
 
 4.水平内容约束流式布局
    orientation为MyLayoutViewOrientation_Horz,arrangedCount为0,不支持wrapContentHeight,支持wrapContentWidth,支持autoArrange。
 
 流式布局支持子视图的宽度依赖于高度或者高度依赖于宽度,以及高度或者宽度依赖于流式布局本身的高度或者宽度
 */
@interface MyFlowLayout : MyBaseLayout

/**
 *初始化一个流式布局并指定布局的方向和布局的数量,如果数量为0则表示内容约束流式布局
 */
-(id)initWithOrientation:(MyLayoutViewOrientation)orientation arrangedCount:(NSInteger)arrangedCount;
+(id)flowLayoutWithOrientation:(MyLayoutViewOrientation)orientation arrangedCount:(NSInteger)arrangedCount;

/**
 *流式布局的方向：
 *如果是MyLayoutViewOrientation_Vert则表示从左到右，从上到下的垂直布局方式，这个方式是默认方式。
 *如果是MyLayoutViewOrientation_Horz则表示从上到下，从左到右的水平布局方式
 */
@property(nonatomic,assign)  MyLayoutViewOrientation orientation;


/**
 *流式布局内所有子视图的整体停靠对齐位置设定。
 *MyMarginGravity_Vert_Top,MyMarginGravity_Vert_Center,MyMarginGravity_Vert_Bottom 表示整体垂直居上，居中，居下
 *MyMarginGravity_Horz_Left,MyMarginGravity_Horz_Center,MyMarginGravity_Horz_Right 表示整体水平居左，居中，居右
 *MyMarginGravity_Vert_Between 表示在流式布局里面，每行之间的行间距都被拉伸，以便使里面的子视图垂直方向填充满整个布局视图。
 *MyMarginGravity_Horz_Between 表示在流式布局里面，每列之间的列间距都被拉伸，以便使里面的子视图水平方向填充满整个布局视图。
 *MyMarginGravity_Vert_Fill 在垂直流式布局里面表示布局会拉伸每行子视图的高度，以便使里面的子视图垂直方向填充满整个布局视图的高度；在水平数量流式布局里面表示每列的高度都相等并且填充满整个布局视图的高度；在水平内容约束布局里面表示布局会自动拉升每列的高度，以便垂直方向填充满布局视图的高度(这种设置方法代替过期的方法：averageArrange)。
 *MyMarginGravity_Horz_Fill 在水平流式布局里面表示布局会拉伸每行子视图的宽度，以便使里面的子视图水平方向填充满整个布局视图的宽度；在垂直数量流式布局里面表示每行的宽度都相等并且填充满整个布局视图的宽度；在垂直内容约束布局里面表示布局会自动拉升每行的宽度，以便水平方向填充满布局视图的宽度(这种设置方法代替过期的方法：averageArrange)。
 */
@property(nonatomic,assign)  MyMarginGravity gravity;


/**
 *指定方向上的子视图的数量，默认是0表示为内容约束流式布局，当数量不为0时则是数量约束流式布局。当值为0时则表示当子视图在方向上的尺寸超过布局视图时则会新起一行或者一列。而如果数量不为0时则：
 如果方向为MyLayoutViewOrientation_Vert，则表示从左到右的数量，当子视图从左往右满足这个数量后新的子视图将会换行再排列
 如果方向为MyLayoutViewOrientation_Horz，则表示从上到下的数量，当子视图从上往下满足这个数量后新的子视图将会换列再排列
 */
@property(nonatomic, assign)  NSInteger arrangedCount;



/**
 *为流式布局提供分页展示的能力,默认是0表不支持分页展示，当设置为非0时则要求必须是arrangedCount的整数倍数，表示每页的子视图的数量。而arrangedCount则表示每排的子视图的数量。当启用pagedCount时要求将流式布局加入到UIScrollView或者其派生类中才能生效。只有数量约束流式布局才支持分页展示的功能，pagedCount和wrapContentHeight以及wrapContentWidth配合使用能实现不同的分页展示能力:
 
 1.垂直数量约束流式布局的wrapContentHeight设置为YES时则以UIScrollView的尺寸作为一页展示的大小，因为指定了一页的子视图数量，以及指定了一排的子视图数量，因此默认也会自动计算出子视图的宽度和高度，而不需要单独指出高度和宽度(子视图的宽度你也可以自定义)，整体的分页滚动是从上到下滚动。(每页布局时从左到右再从上到下排列，新页往下滚动继续排列)：
     1  2  3
     4  5  6
     -------  ↓
     7  8  9
     10 11 12
 
 2.垂直数量约束流式布局的wrapContentWidth设置为YES时则以UIScrollView的尺寸作为一页展示的大小，因为指定了一页的子视图数量，以及指定了一排的子视图数量，因此默认也会自动计算出子视图的宽度和高度，而不需要单独指出高度和宽度(子视图的高度你也可以自定义)，整体的分页滚动是从左到右滚动。(每页布局时从左到右再从上到下排列，新页往右滚动继续排列)
     1  2  3 | 7  8  9
     4  5  6 | 10 11 12
             →
 1.水平数量约束流式布局的wrapContentWidth设置为YES时则以UIScrollView的尺寸作为一页展示的大小，因为指定了一页的子视图数量，以及指定了一排的子视图数量，因此默认也会自动计算出子视图的宽度和高度，而不需要单独指出高度和宽度(子视图的高度你也可以自定义)，整体的分页滚动是从左到右滚动。(每页布局时从上到下再从左到右排列，新页往右滚动继续排列)
     1  3  5 | 7  9   11
     2  4  6 | 8  10  12
             →
 
 2.水平数量约束流式布局的wrapContentHeight设置为YES时则以UIScrollView的尺寸作为一页展示的大小，因为指定了一页的子视图数量，以及指定了一排的子视图数量，因此默认也会自动计算出子视图的宽度和高度，而不需要单独指出高度和宽度(子视图的宽度你也可以自定义)，整体的分页滚动是从上到下滚动。(每页布局时从上到下再从左到右排列，新页往下滚动继续排列)
   
     1  3  5
     2  4  6
    --------- ↓
     7  9  11
     8  10 12
 
 */
@property(nonatomic, assign) NSInteger pagedCount;



/**
 *子视图自动排列,这个属性只有在内容填充约束流式布局下才有用,默认为NO.当设置为YES时则根据子视图的内容自动填充，而不是根据加入的顺序来填充，以便保证不会出现多余空隙的情况。
 *请在将所有子视图添加完毕并且初始布局完成后再设置这个属性，否则如果预先设置这个属性则在后续添加子视图时非常耗性能。
 */
@property(nonatomic,assign)  BOOL autoArrange;


/**
 *流式布局中每排子视图的停靠对齐位置设定。
 如果是MyLayoutViewOrientation_Vert则只用于表示每行子视图的上中下停靠对齐位置，这个属性只支持MyMarginGravity_Vert_Top，MyMarginGravity_Vert_Center,MyMarginGravity_Vert_Bottom,MyMarginGravity_Vert_Fill这里的对齐基础是以每行中的最高的子视图为基准。
 如果是MyLayoutViewOrientation_Horz则只用于表示每列子视图的左中右停靠对齐位置，这个属性只支持MyMarginGravity_Horz_Left，MyMarginGravity_Horz_Center,MyMarginGravity_Horz_Right,MyMarginGravity_Horz_Fill这里的对齐基础是以每列中的最宽的子视图为基准。
 */
@property(nonatomic,assign)  MyMarginGravity arrangedGravity;


/**
 *子视图之间的垂直和水平的间距，默认为0。当子视图之间的间距是固定时可以通过直接设置这两个属性值来指定间距而不需要为每个子视图来设置margin值。
 */
@property(nonatomic ,assign)  CGFloat subviewVertMargin;
@property(nonatomic, assign)  CGFloat subviewHorzMargin;
@property(nonatomic, assign)  CGFloat subviewMargin;  //同时设置水平和垂直间距。




/**
 *在内容约束流式布局的一些应用场景中我们有时候希望某些子视图的宽度是固定的情况下，子视图的间距是浮动的而不是固定的，这样就可以尽可能的容纳更多的子视图。比如每个子视图的宽度是固定80，那么在小屏幕下每行只能放3个，而我们希望大屏幕每行能放4个或者5个子视图。 因此您可以通过如下方法来设置浮动间距，这个方法会根据您当前布局的orientation方向不同而意义不同：
 1.如果您的布局方向是.vert表示设置的是子视图的水平间距，其中的size指定的是子视图的宽度，minSpace指定的是最小的水平间距,maxSpace指定的是最大的水平间距，如果指定的subviewSize计算出的间距大于这个值则会调整subviewSize的宽度。
 2.如果您的布局方向是.horz表示设置的是子视图的垂直间距，其中的size指定的是子视图的高度，minSpace指定的是最小的垂直间距,maxSpace指定的是最大的垂直间距，如果指定的subviewSize计算出的间距大于这个值则会调整subviewSize的高度。
 3.如果您不想使用浮动间距则请将subviewSize设置为0就可以了。
 4.这个方法只在内容约束流式布局里面设置才有意义。
 */
-(void)setSubviewsSize:(CGFloat)subviewSize minSpace:(CGFloat)minSpace maxSpace:(CGFloat)maxSpace;
-(void)setSubviewsSize:(CGFloat)subviewSize minSpace:(CGFloat)minSpace maxSpace:(CGFloat)maxSpace inSizeClass:(MySizeClass)sizeClass;



@end


@interface MyFlowLayout(MyFlowLayoutDeprecated)

/**
 *指定是否均分布局方向上的子视图的宽度或者高度，或者拉伸子视图的尺寸，默认是NO。
 如果是MyLayoutViewOrientation_Vert则表示每行的子视图的宽度会被均分，这样子视图不需要指定宽度，但是布局视图必须要指定一个明确的宽度值，如果设置为YES则wrapContentWidth会失效。
 如果是MyLayoutViewOrientation_Horz则表示每列的子视图的高度会被均分，这样子视图不需要指定高度，但是布局视图必须要指定一个明确的高度值，如果设置为YES则wrapContentHeight会失效。
 内容填充约束流式布局下averageArrange设置为YES时表示拉伸子视图的宽度或者高度以便填充满整个布局视图。
 */
@property(nonatomic,assign)  BOOL averageArrange MYDEPRECATED("use gravity = MyMarginGravity_Horz_Fill or gravity = MyMarginGravity_Vert_Fill to replace");


@end



