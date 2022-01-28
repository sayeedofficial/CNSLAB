import pandas as pd;

data = pd.read_csv("data.csv");
data.drop(['id','Date'],axis=1,inplace=True)
data.head();


x = data.iloc[:100,1:]
y = data.iloc(:100,0)

from sklearn.preprocessing import LabelEncoder,StandardScaler
le = LabelEncoder()
ss = StandardScaler()

x = x.apply(le.fit_transform)
x = ss.fit_transform(x)

from sklearn.model_selection import train_test_split

x_train,x_test,y_train,y_test = train_test_split(x,y,test_size=0.2,random_state=123456)


from sklego.linear_model import LowessRegression

lr = LowessRegression(sigma=0.5,span=0.5)
model = lr.fit(x_train,y_train)
y_pred = model.predict(x_test)

import matplotlib.pyplot as plt

plt.scatter(range(len(y_test)),y_test)
plt.plot(x_train,y_test)
