# C에서 Boolean Array 확장하기 – 신대성 직접 작성

어째피 int를 쓰니까, 그 안의 값을 좀더 활용해보자.

0이면 false인건 여전히 유효하다. 하지만, true일 경우를 1로 제한하지 않는다.

True, False의 판단은 다음과 같이 한다.

```C
if (data[i][j] != 0) true;
if (data[i][j]) true;

if (data[i][j] == 0) false;
if (!data[i][j]) false;

if (data[i][j] < 0) no-next;
if (data[i][j] >= 0) have-next;
```

    근데 쓰다보니 1차원 2차원까지만 쓸수 있을듯? 3차원꺼 가리켜도 될듯

    다음 차원의 첫번째 숫자를 가리키면 될듯

Array 내용이 0이 아니라면, 즉 참이라면, 같은 행의 다음 true가 있는 열을 가리킨다.

만일 다음 true인 열이 존재하지 않으면, -1을 써둔다.

여기에, dataStarter를 도입한다.

이 dataStarter는 data 행의 개수만큼의 크기의 array이다. 그 행의 가장 왼쪽 숫자의 열 index를 가지고있다.

만일 그 행 안에 없으면 -1로 한다.

전부 방문해야 할 때 편할거같다.

```C
int** data;
int* dataStarter;

void VisitAll()
{
    for (int i = 0; i < dataStarter.length; i++)
    {
        int next = dataStarter[i];
        while (1)
        {
            if (next < 0) break;
            Visit(i, next);
            next = visit[i][next];
        }
    }
}

void SetValue(int x, int y)
{
    if (data[x][y])
    {
        printf("already true");
        return;
    }

    if (dataStarter[x] < 0) // when first value in row
    {
        dataStarter[x] = y;
        data[x][y] = -1;
    }
    else if (dataStarter[x] > y) // when have smallest col
    {
        data[x][y] = data[x][dataStarter[x]];
        dataStarter[x] = y;
    }
    else // when have middle or biggest col
    {
        int next = dataStarter[x];
        int prevCol = -1;
        while (next > 0)
        {
            if (next > y)
            {
                break;
            }
            else
            {
                prevCol = next;
                next = data[x][next];
            }
        }
        data[x][prevCol] = y;
        data[x][y] = next;
    }
    return;
}

void ResetValue(int x, int y)
{
    if (!data[x][y])
    {
        printf("already false");
        return;
    }

    int prev = dataStarter[x];
    while (y != data[x][prev]) prev = data[x][prev];
    data[x][prev] = data[x][y];
    data[x][y] = 0;
}
```