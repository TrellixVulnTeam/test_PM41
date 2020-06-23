# 图像分类数据集

## ImageNet类
```
paddlex.datasets.ImageNet(data_dir, file_list, label_list, transforms=None, num_workers=‘auto’, buffer_size=100, parallel_method='thread', shuffle=False)
```
读取ImageNet格式的分类数据集，并对样本进行相应的处理。ImageNet数据集格式的介绍可查看文档:[数据集格式说明](../datasets.md)  

示例：[代码文件](https://github.com/PaddlePaddle/PaddleX/blob/develop/tutorials/train/classification/mobilenetv2.py#L25)

> **参数**

> > * **data_dir** (str): 数据集所在的目录路径。  
> > * **file_list** (str): 描述数据集图片文件和类别id的文件路径（文本内每行路径为相对`data_dir`的相对路径）。  
> > * **label_list** (str): 描述数据集包含的类别信息文件路径。  
> > * **transforms** (paddlex.cls.transforms): 数据集中每个样本的预处理/增强算子，详见[paddlex.cls.transforms](./transforms/cls_transforms.md)。  
> > * **num_workers** (int|str)：数据集中样本在预处理过程中的线程或进程数。默认为'auto'。当设为'auto'时，根据系统的实际CPU核数设置`num_workers`: 如果CPU核数的一半大于8，则`num_workers`为8，否则为CPU核数的一半。  
> > * **buffer_size** (int): 数据集中样本在预处理过程中队列的缓存长度，以样本数为单位。默认为100。  
> > * **parallel_method** (str): 数据集中样本在预处理过程中并行处理的方式，支持'thread'线程和'process'进程两种方式。默认为'process'（Windows和Mac下会强制使用thread，该参数无效）。  
> > * **shuffle** (bool): 是否需要对数据集中样本打乱顺序。默认为False。  

## EasyDataCls类
```
paddlex.datasets.EasyDatasetCls(data_dir, file_list, label_list, transforms=None, num_workers='auto', buffer_size=100, parallel_method='thread', shuffle=False)
```

> 读取EasyData平台标注图像分类数据集，并对样本进行相应的处理。EasyData图像分类任务数据集格式的介绍可查看文档:[数据集格式说明](../datasets.md)。 

> **参数**

> > * **data_dir** (str): 数据集所在的目录路径。  
> > * **file_list** (str): 描述数据集图片文件和对应标注文件的文件路径（文本内每行路径为相对`data_dir`的相对路径）。
> > * **label_list** (str): 描述数据集包含的类别信息文件路径。  
> > * **transforms** (paddlex.seg.transforms): 数据集中每个样本的预处理/增强算子，详见[paddlex.cls.transforms](./transforms/cls_transforms.md)。  
> > * **num_workers** (int|str)：数据集中样本在预处理过程中的线程或进程数。默认为'auto'。当设为'auto'时，根据系统的实际CPU核数设置`num_workers`: 如果CPU核数的一半大于8，则`num_workers`为8，否则为CPU核数的一半。
> > * **buffer_size** (int): 数据集中样本在预处理过程中队列的缓存长度，以样本数为单位。默认为100。  
> > * **parallel_method** (str): 数据集中样本在预处理过程中并行处理的方式，支持'thread'线程和'process'进程两种方式。默认为'process'（Windows和Mac下会强制使用thread，该参数无效）。  
> > * **shuffle** (bool): 是否需要对数据集中样本打乱顺序。默认为False。
