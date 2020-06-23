# 图像分类

## ResNet50类

```python
paddlex.cls.ResNet50(num_classes=1000)
```

> 构建ResNet50分类器，并实现其训练、评估和预测。  

**参数**

> - **num_classes** (int): 类别数。默认为1000。  

### train 训练接口

```python
train(self, num_epochs, train_dataset, train_batch_size=64, eval_dataset=None, save_interval_epochs=1, log_interval_steps=2, save_dir='output', pretrain_weights='IMAGENET', optimizer=None, learning_rate=0.025, warmup_steps=0, warmup_start_lr=0.0, lr_decay_epochs=[30, 60, 90], lr_decay_gamma=0.1, use_vdl=False, sensitivities_file=None, eval_metric_loss=0.05, early_stop=False, early_stop_patience=5, resume_checkpoint=None)
```
>
> **参数**
>
> > - **num_epochs** (int): 训练迭代轮数。
> > - **train_dataset** (paddlex.datasets): 训练数据读取器。
> > - **train_batch_size** (int): 训练数据batch大小。同时作为验证数据batch大小。默认值为64。
> > - **eval_dataset** (paddlex.datasets): 验证数据读取器。
> > - **save_interval_epochs** (int): 模型保存间隔（单位：迭代轮数）。默认为1。
> > - **log_interval_steps** (int): 训练日志输出间隔（单位：迭代步数）。默认为2。
> > - **save_dir** (str): 模型保存路径。
> > - **pretrain_weights** (str): 若指定为路径时，则加载路径下预训练模型；若为字符串'IMAGENET'，则自动下载在ImageNet图片数据上预训练的模型权重；若为None，则不使用预训练模型。默认为'IMAGENET'。
> > - **optimizer** (paddle.fluid.optimizer): 优化器。当该参数为None时，使用默认优化器：fluid.layers.piecewise_decay衰减策略，fluid.optimizer.Momentum优化方法。
> > - **learning_rate** (float): 默认优化器的初始学习率。默认为0.025。
> > - **warmup_steps** (int): 默认优化器的warmup步数，学习率将在设定的步数内，从warmup_start_lr线性增长至设定的learning_rate，默认为0。
> > - **warmup_start_lr**(float): 默认优化器的warmup起始学习率，默认为0.0。
> > - **lr_decay_epochs** (list): 默认优化器的学习率衰减轮数。默认为[30, 60, 90]。
> > - **lr_decay_gamma** (float): 默认优化器的学习率衰减率。默认为0.1。
> > - **use_vdl** (bool): 是否使用VisualDL进行可视化。默认值为False。
> > - **sensitivities_file** (str): 若指定为路径时，则加载路径下敏感度信息进行裁剪；若为字符串'DEFAULT'，则自动下载在ImageNet图片数据上获得的敏感度信息进行裁剪；若为None，则不进行裁剪。默认为None。
> > - **eval_metric_loss** (float): 可容忍的精度损失。默认为0.05。
> > - **early_stop** (bool): 是否使用提前终止训练策略。默认值为False。
> > - **early_stop_patience** (int): 当使用提前终止训练策略时，如果验证集精度在`early_stop_patience`个epoch内连续下降或持平，则终止训练。默认值为5。
> > - **resume_checkpoint** (str): 恢复训练时指定上次训练保存的模型路径。若为None，则不会恢复训练。默认值为None。

### evaluate 评估接口

```python
evaluate(self, eval_dataset, batch_size=1, epoch_id=None, return_details=False)
```
>
> **参数**
>
> > - **eval_dataset** (paddlex.datasets): 验证数据读取器。
> > - **batch_size** (int): 验证数据批大小。默认为1。
> > - **epoch_id** (int): 当前评估模型所在的训练轮数。
> > - **return_details** (bool): 是否返回详细信息，默认False。
>
> **返回值**
>
> > - **dict**: 当return_details为False时，返回dict, 包含关键字：'acc1'、'acc5'，分别表示最大值的accuracy、前5个最大值的accuracy。
> > - **tuple** (metrics, eval_details): 当`return_details`为True时，增加返回dict，包含关键字：'true_labels'、'pred_scores'，分别代表真实类别id、每个类别的预测得分。

### predict 预测接口

```python
predict(self, img_file, transforms=None, topk=5)
```

> 分类模型预测接口。需要注意的是，只有在训练过程中定义了eval_dataset，模型在保存时才会将预测时的图像处理流程保存在`ResNet50.test_transforms`和`ResNet50.eval_transforms`中。如未在训练时定义eval_dataset，那在调用预测`predict`接口时，用户需要再重新定义test_transforms传入给`predict`接口。

> **参数**
>
> > - **img_file** (str): 预测图像路径。
> > - **transforms** (paddlex.cls.transforms): 数据预处理操作。
> > - **topk** (int): 预测时前k个最大值。

> **返回值**
>
> > - **list**: 其中元素均为字典。字典的关键字为'category_id'、'category'、'score'，
> >       分别对应预测类别id、预测类别标签、预测得分。

## 其它分类器类

PaddleX提供了共计22种分类器，所有分类器均提供同`ResNet50`相同的训练`train`，评估`evaluate`和预测`predict`接口，各模型效果可参考[模型库](https://paddlex.readthedocs.io/zh_CN/latest/appendix/model_zoo.html)。

### ResNet18
```python
paddlex.cls.ResNet18(num_classes=1000)
```

### ResNet34
```python
paddlex.cls.ResNet34(num_classes=1000)
```


### ResNet50
```python
paddlex.cls.ResNet50(num_classes=1000)
```

### ResNet50_vd
```python
paddlex.cls.ResNet50_vd(num_classes=1000)
```

### ResNet50_vd_ssld
```python
paddlex.cls.ResNet50_vd_ssld(num_classes=1000)
```

### ResNet101
```python
paddlex.cls.ResNet101(num_classes=1000)
```

### ResNet101_vd
```python
paddlex.cls.ResNet101_vdnum_classes=1000)
```

### ResNet101_vd_ssld
```python
paddlex.cls.ResNet101_vd_ssld(num_classes=1000)
```

### DarkNet53
```python
paddlex.cls.DarkNet53(num_classes=1000)
```

### MobileNetV1
```python
paddlex.cls.MobileNetV1(num_classes=1000)
```

### MobileNetV2
```python
paddlex.cls.MobileNetV2(num_classes=1000)
```

### MobileNetV3_small
```python
paddlex.cls.MobileNetV3_small(num_classes=1000)
```

### MobileNetV3_small_ssld
```python
paddlex.cls.MobileNetV3_small_ssld(num_classes=1000)
```

### MobileNetV3_large
```python
paddlex.cls.MobileNetV3_large(num_classes=1000)
```

### MobileNetV3_large_ssld
```python
paddlex.cls.MobileNetV3_large_ssld(num_classes=1000)
```

### Xception65
```python
paddlex.cls.Xception65(num_classes=1000)
```

### Xception71
```python
paddlex.cls.Xception71(num_classes=1000)
```

### ShuffleNetV2
```python
paddlex.cls.ShuffleNetV2(num_classes=1000)
```

### DenseNet121
```python
paddlex.cls.DenseNet121(num_classes=1000)
```

### DenseNet161
```python
paddlex.cls.DenseNet161(num_classes=1000)
```

### DenseNet201
```python
paddlex.cls.DenseNet201(num_classes=1000)
```

### HRNet_W18
```python
paddlex.cls.HRNet_W18(num_classes=1000)
```
