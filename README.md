## 概述
活体检测 (眨眼，摇头，点头，张嘴，远近，炫彩)，支持鸿蒙Next, Android, IOS 前后端结合，确保活体检测结果安全可靠。(***可用于实人认证，刷脸认证，活体检测等场景***)



演示如下：

![DEMO](https://rd-esand-dev.oss-cn-shanghai.aliyuncs.com/imgs/fldt/demo.gif?OSSAccessKeyId=LTAI5tNZJG7Rz5icyxCpxDNg&Expires=1769387080&Signature=vMiou2asyp2kMdOUigTIP472Dxs%3D)

- H5 体验DEMO链接 ： [https://dev.esandcloud.com/h5demo/esand/living](https://dev.esandcloud.com/h5demo/esand/living)
- 详细接入文档：[https://esandinfo.yuque.com/yv6e1k/aa4qsg/umpa9zl97is8mx5a](https://esandinfo.yuque.com/yv6e1k/aa4qsg/umpa9zl97is8mx5a)

## 接口文档

### 导入插件

```typescript
import { UTS_VerifyInit, UTS_StartLDT, EsLivingDetectResult } from "@/uni_modules/esand-ldt"
```

### API 接口

#### 1. UTS_VerifyInit - 认证初始化

在开始活体检测之前，需要先调用此接口进行初始化。

**函数签名：**
```typescript
UTS_VerifyInit(initConfigString: string): Promise<EsLivingDetectResult>
```

**参数说明：**

`initConfigString` (string): JSON字符串格式的配置对象，包含以下字段：

| 参数名 | 类型 | 必填 | 说明 |
|--------|------|------|------|
| livingType | number | 是 | 活体类型。1：远近，2：眨眼，3：摇头，4：点头，5：张嘴，6：炫彩。支持多动作组合，如传入 `12` 表示先做远近活体，后做眨眼活体。一次最多支持4组动作组合 |
| needVideo | boolean | 否 | 是否需要录制视频，默认为 `false` |
| useStrictMode | number | 否 | 是否使用严格模式。1：严格模式，0：非严格模式。非严格模式下，炫彩环境检查不通过会使用其他的活体动作，默认为 `0` |
| cameraDeviceId | number | 否 | 相机ID。0：后置摄像头，1：前置摄像头（默认） |
| autoRedirects | boolean | 否 | 是否跳转到 returnURL 页面。如果为 `false`，不跳转，直接在调用页面返回执行结果。**请固定为 `false`** |

**返回值：**

返回 `Promise<EsLivingDetectResult>`，包含以下字段：

| 字段名 | 类型 | 说明 |
|--------|------|------|
| code | string | 状态码。`ELD_SUCCESS`：成功，`ELD_FAILED`：失败，`ELD_PARAME_ERROR`：参数异常，`ELD_EXCEPTION`：发生异常，`ELD_UNSUPPORT`：不支持此活体类型 |
| msg | string | 执行结果描述 |
| data | string | 执行结果数据，用于后续调用服务器接口获取 token |

**使用示例：**

```typescript
const configData = {
  livingType: 6,           // 炫彩活体
  needVideo: true,         // 需要录制视频
  useStrictMode: 1,        // 严格模式
  cameraDeviceId: 1,       // 前置摄像头
  autoRedirects: false     // 不跳转
};

const res = await UTS_VerifyInit(JSON.stringify(configData));
if (res.code === 'ELD_SUCCESS') {
  // 初始化成功，使用 res.data 调用服务器接口获取 token
  console.log('初始化数据：', res.data);
} else {
  console.error('初始化失败：', res.msg);
}
```

---

#### 2. UTS_StartLDT - 发起活体检测

在获取到服务器返回的 token 后，调用此接口开始活体检测流程。

**函数签名：**
```typescript
UTS_StartLDT(token: string): Promise<EsLivingDetectResult>
```

**参数说明：**

`token` (string): JSON字符串格式的对象，包含以下字段：

| 参数名 | 类型 | 必填 | 说明 |
|--------|------|------|------|
| token | string | 是 | 服务器返回的 token，通过调用服务器初始化接口获取 |

**返回值：**

返回 `Promise<EsLivingDetectResult>`，包含以下字段：

| 字段名 | 类型 | 说明 |
|--------|------|------|
| code | string | 状态码。`ELD_SUCCESS`：成功，`ELD_FAILED`：失败，`ELD_PARAME_ERROR`：参数异常，`ELD_EXCEPTION`：发生异常，`ELD_UNSUPPORT`：不支持此活体类型 |
| msg | string | 执行结果描述 |
| data | string | 执行结果数据，用于后续调用服务器验证接口 |
| token | string | token 值 |
| videopath | string | 视频文件路径（如果 `needVideo` 为 `true` 时返回） |

**使用示例：**

```typescript
// token 从服务器初始化接口获取
const tokenData = {
  token: 'your_token_from_server'
};

const result = await UTS_StartLDT(JSON.stringify(tokenData));
if (result.code === 'ELD_SUCCESS') {
  // 活体检测成功，使用 result.data 调用服务器验证接口
  console.log('检测结果数据：', result.data);
  if (result.videopath) {
    console.log('视频路径：', result.videopath);
  }
} else {
  console.error('活体检测失败：', result.msg);
}
```

---

### 完整使用流程

1. **调用 `UTS_VerifyInit` 进行初始化**
   ```typescript
   const initResult = await UTS_VerifyInit(JSON.stringify(configData));
   ```

2. **将初始化返回的 `data` 发送到服务器获取 token**
   ```typescript
   // 调用服务器接口（建议放在服务器端，保护 APPCODE）
   const serverResponse = await uni.request({
     url: 'your_server_init_url',
     method: 'POST',
     data: { initMsg: initResult.data }
   });
   const token = serverResponse.data.token;
   ```

3. **调用 `UTS_StartLDT` 开始活体检测**
   ```typescript
   const detectResult = await UTS_StartLDT(JSON.stringify({ token }));
   ```

4. **将检测结果发送到服务器进行验证**
   ```typescript
   // 调用服务器验证接口（建议放在服务器端，保护 APPCODE）
   await uni.request({
     url: 'your_server_verify_url',
     method: 'POST',
     data: {
       token: detectResult.token,
       verifyMsg: detectResult.data
     }
   });
   ```

### 活体类型说明

| 类型值 | 名称 | 说明 |
|--------|------|------|
| 1 | 远近 | 需要用户将脸部靠近或远离摄像头 |
| 2 | 眨眼 | 需要用户眨眼 |
| 3 | 摇头 | 需要用户左右摇头 |
| 4 | 点头 | 需要用户上下点头 |
| 5 | 张嘴 | 需要用户张嘴 |
| 6 | 炫彩 | 需要用户在炫彩光效下完成检测 |

**多动作组合：**
- 支持多个动作组合，如 `12` 表示先做远近，后做眨眼
- 一次最多支持 4 组动作组合
- 组合方式：将多个类型值拼接成数字，如 `123` 表示先远近、再眨眼、再摇头

### 注意事项

1. **APPCODE 安全**：为了保护 APPCODE，建议将服务器接口调用逻辑放在服务器端，客户端通过自己的服务器转发请求。

2. **权限配置**：使用前请确保在 `manifest.json` 中配置了相机权限：
   - Android: `android.permission.CAMERA`
   - iOS: `NSCameraUsageDescription`
   - 鸿蒙: 相机权限配置

3. **错误处理**：请务必检查返回的 `code` 字段，只有 `ELD_SUCCESS` 表示操作成功。

4. **视频录制**：如果设置了 `needVideo: true`，检测完成后可通过 `videopath` 字段获取视频文件路径。

## 联系我

有任何疑问或者问题，可通过如下方式联系我


`Wechat Number:` esand_info </br>
`QQ Number:` 3626921591 </br>
`Phone Number:` +8613691664797</br>
`Email:` reid.li@foxmail.com</br>
`Telegram:` [@R90000000](https://t.me/R90000000)</br>


Wechat QR CODE :

![QRCODE](https://rd-esand-dev.oss-cn-shanghai.aliyuncs.com/imgs/comms/qrcode.jpeg?OSSAccessKeyId=LTAI5tNZJG7Rz5icyxCpxDNg&Expires=1801787024&Signature=GTU7tPcXKD2PqHHHrJ2sqEfBaqQ%3D)
